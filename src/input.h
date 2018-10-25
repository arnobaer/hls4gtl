#ifndef gtl_input_h
#define gtl_input_h

#include <cstddef> // for size_t
#include <ap_int.h>
#include "definitions.h"

#include "gtl/object.h"
#include "gtl/utils/array.h"

// TODO review

struct in_data_t
{
    typedef gtl::object::eg eg_type;
    typedef gtl::object::jet jet_type;
    typedef gtl::object::tau tau_type;
    typedef gtl::object::muon muon_type;
    typedef gtl::object::asymmetry asymmetry_type;
    typedef gtl::object::centrality centrality_type;
    typedef gtl::object::external external_type;
    typedef size_t size_type;

    static const size_type calo_size = 12;
    static const size_type muon_size = 8;

    gtl::utils::array<eg_type, calo_size> eg;
    gtl::utils::array<jet_type, calo_size> jet;
    gtl::utils::array<tau_type, calo_size> tau;
    gtl::utils::array<muon_type, muon_size> muon;
    asymmetry_type asymmetry_et;
    asymmetry_type asymmetry_ht;
    asymmetry_type asymmetry_ethf;
    asymmetry_type asymmetry_hthf;
    centrality_type centrality;
    external_type external;
};

#endif
