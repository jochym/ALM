/*
 suggest_Si.cpp

 This is an example to run ALM in the suggest mode.

*/
#include "alm.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

void show_fc(ALM_NS::ALM *alm, const int fc_order)
{
    int fc_length = alm->get_number_of_fc_elements(fc_order); // harmonic=1, ...
    std::cout << "fc_length: " << fc_length << std::endl;

    int n = fc_order + 1;

    double fc_value[fc_length];
    int elem_indices[fc_length * n];

    alm->get_fc_origin(fc_value, elem_indices, fc_order);

    for (int i = 0; i < fc_length; i++) {
        std::cout << i + 1 << ":" << " " << fc_value[i] << " ";

        for (int j = 0; j < n; j++) {
            std::cout << elem_indices[i * n + j] / 3 + 1 << "-" <<
                elem_indices[i * n + j] % 3 + 1 << " ";
        }
        std::cout << std::endl;
    }
}

void show_fc_all(ALM_NS::ALM *alm, const int fc_order)
{
    int fc_length = alm->get_number_of_fc_elements(fc_order);
    int ntran = alm->get_atom_mapping_by_pure_translations()[0].size();
    fc_length *= ntran;
    std::cout << "fc_length: " << fc_length << std::endl;

    int n = fc_order + 1;

    double fc_value[fc_length];
    int elem_indices[fc_length * n];

    alm->get_fc_all(fc_value, elem_indices, fc_order);

    for (int i = 0; i < fc_length; i++) {
        std::cout << i + 1 << ":" << " " << fc_value[i] << " ";

        for (int j = 0; j < n; j++) {
            std::cout << elem_indices[i * n + j] / 3 + 1 << "-" <<
                elem_indices[i * n + j] % 3 + 1 << " ";
        }
        std::cout << std::endl;
    }
}

void parse_displacement_and_force_files(double *u,
					double *f,
					const int nat,
					const int ndata,
					const int nstart,
					const int nend,
					const std::string file_disp,
					const std::string file_force)
{
    int i, j, k;
    int idata;
    double u_in, f_in;
    unsigned int nline_f, nline_u;
    unsigned int nreq;

    std::ifstream ifs_disp, ifs_force;

    ifs_disp.open(file_disp.c_str(), std::ios::in);
    if (!ifs_disp) {
	std::cout << "openfiles" << "cannot open disp file" << std::endl;
        exit(0);
    }
    ifs_force.open(file_force.c_str(), std::ios::in);
    if (!ifs_force) {
	std::cout << "openfiles" << "cannot open force file" << std::endl;
        exit(0);
    }

    nreq = 3 * nat * ndata;

    double u_tmp[nreq];
    double f_tmp[nreq];

    // Read displacements from DFILE

    nline_u = 0;
    while (ifs_disp >> u_in) {
        u_tmp[nline_u++] = u_in;
        if (nline_u == nreq) break;
    }

    if (nline_u < nreq) {
        std::cout << "data_multiplier"
                  << "The number of lines in DFILE is too small for the given NDATA = "
                  << ndata << std::endl;
        exit(0);
    }

    // Read forces from FFILE
    nline_f = 0;
    while (ifs_force >> f_in) {
        f_tmp[nline_f++] = f_in;
        if (nline_f == nreq) break;
    }

    if (nline_f < nreq) {
        std::cout << "data_multiplier"
                  << "The number of lines in FFILE is too small for the given NDATA = "
                  << ndata << std::endl;
        exit(0);
    }

    idata = 0;
    for (i = 0; i < ndata; ++i) {
	if (i < nstart - 1) continue;
	if (i > nend - 1) break;

	for (j = 0; j < nat; ++j) {
	    for (k = 0; k < 3; ++k) {
		u[3 * nat * idata + 3 * j + k] = u_tmp[3 * nat * i + 3 * j + k];
		f[3 * nat * idata + 3 * j + k] = f_tmp[3 * nat * i + 3 * j + k];
	    }
	}
	++idata;
    }

    ifs_disp.close();
    ifs_force.close();
}

int main()
{
    ALM_NS::ALM *alm = new ALM_NS::ALM();

    double lavec[3][3] = {{20.406, 0, 0},
                          {0, 20.406, 0},
                          {0, 0, 20.406}};
    double xcoord[][3] =
        {{ 0.0000000000000000, 0.0000000000000000, 0.0000000000000000},
         { 0.0000000000000000, 0.0000000000000000, 0.5000000000000000},
         { 0.0000000000000000, 0.2500000000000000, 0.2500000000000000},
         { 0.0000000000000000, 0.2500000000000000, 0.7500000000000000},
         { 0.0000000000000000, 0.5000000000000000, 0.0000000000000000},
         { 0.0000000000000000, 0.5000000000000000, 0.5000000000000000},
         { 0.0000000000000000, 0.7500000000000000, 0.2500000000000000},
         { 0.0000000000000000, 0.7500000000000000, 0.7500000000000000},
         { 0.1250000000000000, 0.1250000000000000, 0.1250000000000000},
         { 0.1250000000000000, 0.1250000000000000, 0.6250000000000000},
         { 0.1250000000000000, 0.3750000000000000, 0.3750000000000000},
         { 0.1250000000000000, 0.3750000000000000, 0.8750000000000000},
         { 0.1250000000000000, 0.6250000000000000, 0.1250000000000000},
         { 0.1250000000000000, 0.6250000000000000, 0.6250000000000000},
         { 0.1250000000000000, 0.8750000000000000, 0.3750000000000000},
         { 0.1250000000000000, 0.8750000000000000, 0.8750000000000000},
         { 0.2500000000000000, 0.0000000000000000, 0.2500000000000000},
         { 0.2500000000000000, 0.0000000000000000, 0.7500000000000000},
         { 0.2500000000000000, 0.2500000000000000, 0.0000000000000000},
         { 0.2500000000000000, 0.2500000000000000, 0.5000000000000000},
         { 0.2500000000000000, 0.5000000000000000, 0.2500000000000000},
         { 0.2500000000000000, 0.5000000000000000, 0.7500000000000000},
         { 0.2500000000000000, 0.7500000000000000, 0.0000000000000000},
         { 0.2500000000000000, 0.7500000000000000, 0.5000000000000000},
         { 0.3750000000000000, 0.1250000000000000, 0.3750000000000000},
         { 0.3750000000000000, 0.1250000000000000, 0.8750000000000000},
         { 0.3750000000000000, 0.3750000000000000, 0.1250000000000000},
         { 0.3750000000000000, 0.3750000000000000, 0.6250000000000000},
         { 0.3750000000000000, 0.6250000000000000, 0.3750000000000000},
         { 0.3750000000000000, 0.6250000000000000, 0.8750000000000000},
         { 0.3750000000000000, 0.8750000000000000, 0.1250000000000000},
         { 0.3750000000000000, 0.8750000000000000, 0.6250000000000000},
         { 0.5000000000000000, 0.0000000000000000, 0.0000000000000000},
         { 0.5000000000000000, 0.0000000000000000, 0.5000000000000000},
         { 0.5000000000000000, 0.2500000000000000, 0.2500000000000000},
         { 0.5000000000000000, 0.2500000000000000, 0.7500000000000000},
         { 0.5000000000000000, 0.5000000000000000, 0.0000000000000000},
         { 0.5000000000000000, 0.5000000000000000, 0.5000000000000000},
         { 0.5000000000000000, 0.7500000000000000, 0.2500000000000000},
         { 0.5000000000000000, 0.7500000000000000, 0.7500000000000000},
         { 0.6250000000000000, 0.1250000000000000, 0.1250000000000000},
         { 0.6250000000000000, 0.1250000000000000, 0.6250000000000000},
         { 0.6250000000000000, 0.3750000000000000, 0.3750000000000000},
         { 0.6250000000000000, 0.3750000000000000, 0.8750000000000000},
         { 0.6250000000000000, 0.6250000000000000, 0.1250000000000000},
         { 0.6250000000000000, 0.6250000000000000, 0.6250000000000000},
         { 0.6250000000000000, 0.8750000000000000, 0.3750000000000000},
         { 0.6250000000000000, 0.8750000000000000, 0.8750000000000000},
         { 0.7500000000000000, 0.0000000000000000, 0.2500000000000000},
         { 0.7500000000000000, 0.0000000000000000, 0.7500000000000000},
         { 0.7500000000000000, 0.2500000000000000, 0.0000000000000000},
         { 0.7500000000000000, 0.2500000000000000, 0.5000000000000000},
         { 0.7500000000000000, 0.5000000000000000, 0.2500000000000000},
         { 0.7500000000000000, 0.5000000000000000, 0.7500000000000000},
         { 0.7500000000000000, 0.7500000000000000, 0.0000000000000000},
         { 0.7500000000000000, 0.7500000000000000, 0.5000000000000000},
         { 0.8750000000000000, 0.1250000000000000, 0.3750000000000000},
         { 0.8750000000000000, 0.1250000000000000, 0.8750000000000000},
         { 0.8750000000000000, 0.3750000000000000, 0.1250000000000000},
         { 0.8750000000000000, 0.3750000000000000, 0.6250000000000000},
         { 0.8750000000000000, 0.6250000000000000, 0.3750000000000000},
         { 0.8750000000000000, 0.6250000000000000, 0.8750000000000000},
         { 0.8750000000000000, 0.8750000000000000, 0.1250000000000000},
         { 0.8750000000000000, 0.8750000000000000, 0.6250000000000000}};
    int nkd = 1;
    int kd[64] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::string kdname[1] = {"Si"};

    int nat = 64;
    int ndata = 21;
    int nstart = 1;
    int nend = 21;
    int ndata_used = nend - nstart + 1;
    int nbody_include[2] = {2, 3};
    double cutoff_radii[2] = {-1.0, 7.3};
    // Run
    alm->set_verbosity(0); 
    alm->set_run_mode("optimize");
    alm->set_output_filename_prefix("si222API");
    alm->set_cell(64, lavec, xcoord, kd, kdname);
    alm->define(2, nkd, nbody_include, cutoff_radii);

    double u[ndata_used * nat * 3];
    double f[ndata_used * nat * 3];
    parse_displacement_and_force_files
	(u, f, nat, ndata, nstart, nend,
	 "disp.dat", "force.dat");
    alm->set_displacement_and_force(u, f, nat, ndata_used);

    alm->run();

    for (int fc_order = 1; fc_order < 3; fc_order++) {
//        show_fc(alm, fc_order);
         show_fc_all(alm, fc_order);
    }
    delete alm;

    return 1;
}
