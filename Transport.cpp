/*
 Author: Blake
 Date: 11/21/17
 Main File
 */


#include "Transport.h"
using std::make_shared;


Transport::Transport(Geometry geoin, Constants consti , int numhis): geometry(geoin) , constants(consti) , numHis(numhis) {}

/*
void Transport::setup()
 {
 
 //read input file if it existed
 //plane at x = 0 and at x = 10 -> cell1
 //material
 vector<double> sigt;
 vector<double> siga;
 vector<double> sigsi;
 vector<vector<double>> sigso;
 sigt.push_back(1.0);
 siga.push_back(0.5);
 sigsi.push_back(0.5);
 sigso.push_back(sigsi);
 Material mat1 = Material(1, sigt, siga, sigso);
 
 
 //bounds
 Surf_ptr plane1 = plane1("plane1", 0.0, 0.0, 1.0, 0.0);
 Surf_ptr plane2 = make_shared<plane>("plane2", 0.0, 0.0, 1.0, 5.0);
 //vector<bool> inside1;
 //inside1.push_back(false); //false -> outside, true -> inside
 //inside1.push_back(true);
 //vector<Surf_ptr> cellSurfaces1;
 vector<pair<Surf_ptr, bool>> cellSurfaces1;
 cellSurfaces1.push_back(plane1);
 cellSurfaces1.push_back(plane2);
 
 //create cell 
 Cell_ptr cell1 = make_shared<Cell>(mat1, cellSurfaces1, inside1);
 
 //add to the geometry
 geometry.addMaterial(mat1);
 surfaces.push_back(plane1);
 surfaces.push_back(plane2);
 cells.push_back(cell1);
 
 
 
 
 }
*/
 

void Transport::runTransport()
{
	vector<double> sourceGroups;
	sourceGroups.push_back(1.0);
	sourceGroups.push_back(0.0);
	setSourceSphere psource = setSourceSphere(0.0, 0.0, 0.0, 0.0, 3.0, sourceGroups);
    for(int i = 0; i < numHis ; i++)
    {
		//sample src 
		Part_ptr p_new = psource.sample();
		Cell_ptr startingCell = geometry.whereAmI(p_new->getPos());
		p_new->setCell(startingCell);
		pstack.push(p_new);
          
        //run history
        while(!pstack.empty())
        {
           std::cout << "\nRunning another history\n" << std::endl;

            Part_ptr p = pstack.top();
            while(p->isAlive())
            {
			//p->printState();
                Cell_ptr current_Cell = p->getCell();

                double d2s = current_Cell->distToSurface(p);
                double d2c = current_Cell->distToCollision(p);
                
                if(d2s > d2c) //collision!
                {
				cout << "collided" << endl;
                    //score collision tally in current cell
                    current_Cell->scoreTally(p , current_Cell->getMat()->getTotalXS( p->getGroup() ) ); 
                    
                    p->move(d2c);
                    current_Cell->processRxn(p, pstack);

                }
                else //hit surface
                {
				cout << "hit surface" << endl;
				cout << "moving from " << p->getCell()->name << endl;
                    p->move(d2s + 0.00001);
                    Cell_ptr newCell = geometry.whereAmI(p->getPos());
				if(newCell == nullptr)
				{
					p->kill();
				}
				else
				{
					p->setCell(newCell);
				}
                }

                //tell all estimators that the history had ended
                for( auto cell : geometry.getCells() ) {
                    cell->endTallyHist();
                }
            }
            pstack.pop();
        }
    }
}
void Transport::output()
{
    cout << "Total Number of Histories: " << numHis << endl;

    int i = 0;
    for( Cell_ptr cell : geometry.getCells() ) {
        ++i;
        std::cout << "Collision tally in cell " << i << std::endl;
        for( int j = 1; j <= constants.getNumGroups(); ++j) {
            std::cout << " group: " << j << ", tally = " << cell->getSingleGroupTally(j).first 
                           << ", stddev = " << cell->getSingleGroupTally(j).second << std::endl;
        }
        cout << std::endl;
    }
}
