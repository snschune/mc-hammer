# mc-hammer
3D Monte Carlo neutron transport

This is a 3D Monte Carlo neutron transport code developed at the University of Michigan.

called from command line as:
> ./a.out number_of_histories number_of_groups xs_filename mesh_filename

## Example
> ./a.out 100000 2 Berp.xs coarse.thrm

This would correspond to 100000 histories, 2 energy groups, xs_filename='Berp.xs', mesh_filename='coarse.thrm'

### Note
*   Cross section file must be located in the directory "XSFiles/".
*   Mesh file must be located in the directory "MeshFiles/"

## Cross section file formatted as:

>**Line 1**: number of materials
>
>**Block 1**: each entry in this block contains cross sections for a single material. Each entry contains  L\*G+ 6 lines.
>>**Entry line 1**: material_id
>>
>>**Entry line 2**: fission_spectrum_1 fission_spectrum_2 … fission_spectrum_G
>>
>>**Entry line 3**: energy_group_boundary_1 energy_group_boundary_3 … energy_group_boundary_G
>>
>>**Entry line 4**: fission_xs_1 fission_xs_2 fission_xs_3 … fission_xs_G
>>
>>**Entry line 5**: nu_bar_1 nu_bar_2 … nu_bar_G
>>
>>**Entry line 6**: total_xs_1 total_xs_2 … total_xs_G
>>
>>**Entry line 7**: sig_scat_{0, 1->1} sig_scat_{0, 2->1} … sig_scat_{0, G->1}
>>
>>**Entry line 8**: sig_scat_{0, 1->2} sig_scat_{0, 2->2} … sig_scat_{0, G->2}
>>
>>        :
>>**Entry line G + 6**: sig_scat_{0, 1->G} sig_scat_{0, 2->G} … sig_scat_{0, G->G}
>>
>>**Entry line G + 7**: sig_scat_{1, 1->1} sig_scat_{1, 2->1} … sig_scat_{1, G->1}
>>
>>**Entry line G + 8**: sig_scat_{1, 1->2} sig_scat_{1, 2->2} … sig_scat_{1, G->2}
>>
>>        :
>>**Entry line 2 \* G + 6**: sig_scat_{1, 1->G} sig_scat_{1, 2->G} … sig_scat_{1, G->G}
>>
>>        :


### Explanation:
1.	G = total number of groups.
2.	L = scattering expansion.
3.	fission_spectrum_g: fraction of neutrons born in fission that appear in energy group g.
4.	energy_group_boundary_g: currently unused, can be filled with 0s. Upper bound of energy group g.
5.	fission_xs_g: fission cross section (NOTE: not nu_bar * fission_xs) in group g.
6.	nu_bar_g: average number of neutrons released by fission caused by a neutron in energy group g.
7.	total_xs_g: total cross section in energy group g.
8.	sig_scat_{l, g'->g}: l-th Legendre polynomial moment of the scattering cross section from group g' to g. The (2 * l + 1) factor may be included in the value of the cross section or not, THOR can handle both cases. It needs to be specified separately every time.


## Mesh file formatted as:

## Output

All output files are written to the "OutFiles/" directory

*  Mesh tally file is currently hardcoded as "mesh.out"
*  Timing results file is currently hardcoded as "time.out"
*  Mesh tally xml-style VTK file is currently hardcoded as "mesh_tallies.vtu"
	-  VTK files can be opened with ParaView. FaraView is an open-source, multi-platform data analysis and visualization application. You can [download Paraview here](https://www.paraview.org/download/).
