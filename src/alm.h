/*
 alm.h

 Copyright (c) 2014, 2015, 2016 Terumasa Tadano

 This file is distributed under the terms of the MIT license.
 Please see the file 'LICENCE.txt' in the root directory 
 or http://opensource.org/licenses/mit-license.php for information.
*/

#pragma once

#include <string>

namespace ALM_NS
{
    class ALM
    {
    public:
        ALM();
        ~ALM();

        std::string mode;
        int verbosity;

        class InputSetter *input;
        class System *system;
        class Interaction *interaction;
        class Fcs *fcs;
        class Symmetry *symmetry;
        class Fitting *fitting;
        class Constraint *constraint;
        class Files *files;
        class Displace *displace;
        class Timer *timer;

        void set_run_mode(std::string mode_in);
        void set_verbosity(int verbosity_in);
        void set_output_filename_prefix(std::string prefix) const;
        void set_is_print_symmetry(int printsymmetry);
        void set_is_print_hessians(bool print_hessian);
        void set_symmetry_param(int nsym);
        void set_symmetry_tolerance(double tolerance);
        void set_displacement_param(bool trim_dispsign_for_evenfunc);
        void set_displacement_basis(std::string str_disp_basis);
        void set_periodicity(const int is_periodic[3]);
        void set_cell(int nat,
                      const double lavec[3][3],
                      const double xcoord[][3],
                      const int kd[],
                      const std::string kdname[]);
        void set_magnetic_params(const double *magmom,
                                 bool lspin,
                                 int noncollinear,
                                 int trev_sym_mag,
                                 std::string str_magmom);
        void set_displacement_and_force(const double *u_in,
                                        const double *f_in,
                                        int nat,
                                        int ndata_used);
        int get_ndata_used();
        void set_constraint_type(int constraint_flag);
        void set_rotation_axis(std::string rotation_axis);
        void set_sparse_mode(int sparse_mode);
        void set_fitting_filenames(std::string dfile,
                                   std::string ffile);
        void set_norder(int maxorder);
        void set_nbody_include(const int *nbody_include);
        void set_cutoff_radii(const double *rcs);

        int get_atom_mapping_by_pure_translations(int *map_p2s);
        int get_number_of_displacement_patterns(int fc_order); // harmonic=1, ...
        void get_numbers_of_displacements(int *numbers,
                                          int fc_order); // harmonic=1, ...
        int get_displacement_patterns(int *atom_indices,
                                      double *disp_patterns,
                                      int fc_order); // harmonic=1, ...
        int get_number_of_fc_elements(int fc_order); // harmonic=2, ...
        int get_number_of_irred_fc_elements(int fc_order); // harmonic=2, ...

        void get_fc_origin(double *fc_values,
                           int *elem_indices,
                           // (len(fc_value), fc_order) is flatten.
                           int fc_order); // harmonic=2, ...


        void get_fc_irreducible(double *fc_values,
                                int *elem_indices,
                                // (len(fc_value), fc_order) is flatten.
                                int fc_order); // harmonic=2, ...


        void get_fc_all(double *fc_values,
                        int *elem_indices,
                        // (len(fc_value), fc_order) is flatten.
                        int fc_order); // harmonic=2, ...

        void set_fc(double *fc_in);

        void get_matrix_elements(int nat,
                                 int ndata_used,
                                 double *amat,
                                 double *bvec);
        void generate_force_constant();
        int optimize();
        void run_suggest();
        void run();

    private:

        bool structure_initialized;
        bool ready_to_fit;
        std::ofstream *ofs_alm;
        std::streambuf *coutbuf;
        void create();
        void initialize_structure(ALM *);
        void initialize_interaction(ALM *alm);
    };
}
