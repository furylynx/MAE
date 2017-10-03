//
// Created by furylynx on 03.10.17.
//

#ifndef MAE_GENERAL_SKELETON_BASE_PAIR_H
#define MAE_GENERAL_SKELETON_BASE_PAIR_H

//custom includes
#include "math/basis.hpp"
#include "general_skeleton.hpp"

//global includes
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <iostream>


namespace mae
{

    class general_skeleton_basis_pair
    {

    public:
        general_skeleton_basis_pair();

        general_skeleton_basis_pair(std::shared_ptr<general_skeleton> skeleton, std::shared_ptr<math::basis> basis);

        virtual ~general_skeleton_basis_pair();

        virtual void set_skeleton(std::shared_ptr<general_skeleton> skeleton);

        virtual std::shared_ptr<general_skeleton> get_skeleton() const;

        virtual void set_basis(std::shared_ptr<math::basis> basis);

        virtual std::shared_ptr<math::basis> get_basis() const;

    private:

        std::shared_ptr<mae::math::basis> basis_;
        std::shared_ptr<mae::general_skeleton> skeleton_;

    };

}


#endif //MAE_GENERAL_SKELETON_BASE_PAIR_H
