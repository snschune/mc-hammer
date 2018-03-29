/*
 Author: Blake
 Date: 11/21/17
 Main File
 */


#include "Transport.h"
using std::make_shared;

//constructor
Transport::Transport(Geom_ptr geoin, Cons_ptr consti, Mesh_ptr meshin , Time_ptr timein): geometry(geoin) , constants(consti), mesh(meshin) , timer(timein) {}
 
void Transport::runTransport()
{
    numHis = constants->getNumHis();
    double tally = 0;
    for( int i = 0; i < numHis; i++ )
    {
        //start a timer
        timer->startHist();

        //sample src 
        Part_ptr p_new = geometry->sampleSource();
        Cell_ptr startingCell = geometry->whereAmI(p_new->getPos());
        p_new->setCell(startingCell);
        pstack.push(p_new);
          
        //run history
        while( !pstack.empty() )
        {
           Part_ptr p = pstack.top();
            while(p->isAlive())
            {
                Cell_ptr current_Cell = p->getCell();

                double d2s = current_Cell->distToSurface(p);
                double d2c = current_Cell->distToCollision(p);

                if(d2s > d2c) //collision!
                {
                    // move particle
                    p->move(d2c);

                    // score collision tally in current cell
                    timer->startTimer("scoring collision tally");
                    current_Cell->scoreTally( p, current_Cell->getMat()->getMacroXS( p ) );
                    timer->endTimer("scoring collision tally");

                    // score mesh tally
                    timer->startTimer("scoring mesh tally");
                    mesh->scoreTally( p, current_Cell->getMat()->getMacroXS( p ) );
                    timer->endTimer("scoring mesh tally");
                    tally++;

                    // sample collision
                    current_Cell->getMat()->sampleCollision( p, pstack );

                    // check number of collisions
                    if ( p->getNCollisions() >= constants->getKillAfterNColl() ) 
                    {
                        p->kill(); 
                    }
                }
                else //hit surface
                {
                    p->move(d2s + 0.00000001); // TODO: convert this to tolerance with Constants
                    Cell_ptr newCell = geometry->whereAmI( p->getPos() );

                    if ( newCell == nullptr ) { p->kill(); }
                    else { p->setCell(newCell); }
                }
            }
            pstack.pop();
        }
        //tell all estimators that the history has ended
        for( auto cell : geometry->getCells() ) { cell->endTallyHist(); }

        // end histories in the mesh
        mesh->endTallyHist();

        // end the history timer
        timer->endHist();
    }
    tally /= numHis;
}

void Transport::output() {
    cout << std::endl << "Total Number of Histories: " << numHis << endl;

    int i = 0;
    for( Cell_ptr cell : geometry->getCells() ) {
        ++i;
        std::cout << "Collision tally in cell " << i << std::endl;
        for( int j = 1; j <= constants->getNumGroups(); ++j) {
            std::cout << " group: " << j << ", tally = " << cell->getSingleGroupTally(j, numHis).first 
                      << ", stddev = " << cell->getSingleGroupTally(j, numHis).second << std::endl;
        }
        cout << std::endl;
    }

    // print timing information
    timer->printAvgResults();

    // print mesh estimators to file
    mesh->printMeshTallies();
    if ( constants->getAllTets() ) {
        mesh->writeToVTK();
    }
}
