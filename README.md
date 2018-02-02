# mc-hammer
3D Monte Carlo neutron transport

This is a 3D Monte Carlo neutron transport code developed at the University of Michigan.

called from command line as:
>> ./a.out number_of_histories number_of_groups xs_filename mesh_filename

## Example
>> ./a.out 100000 2 Berp.xs coarse.thrm

This would correspond to 100,000 histories, 2 energy groups, xs_filname='Berp.xs', mesh_filename='coarse.thrm'

### Note
*   Cross section file must be located in the directory "XSFiles/".
*   Mesh file must be located in the directory "MeshFiles/"

## Cross section file formatted as:

## Mesh file formatted as:

## Output
*  Output file is currently hardcoded as "mesh.out", located in the "OutFiles/" directory
