//
// Created by furylynx on 03.10.17.
//

#include "general_skeleton_basis_pair.hpp"

namespace mae
{
    general_skeleton_basis_pair::general_skeleton_basis_pair()
    {

    }


    general_skeleton_basis_pair::general_skeleton_basis_pair(std::shared_ptr<general_skeleton> skeleton, std::shared_ptr<math::basis> basis)
    {
        skeleton_ = skeleton;
        basis_ = basis;
    }

    general_skeleton_basis_pair::~general_skeleton_basis_pair()
    {
    }

    void general_skeleton_basis_pair::set_skeleton(std::shared_ptr<general_skeleton> skeleton)
    {
        skeleton_ = skeleton;
    }

    std::shared_ptr<general_skeleton> general_skeleton_basis_pair::get_skeleton() const
    {
        return skeleton_;
    }

    void general_skeleton_basis_pair::set_basis(std::shared_ptr<math::basis> basis)
    {
       basis_ = basis;
    }

    std::shared_ptr<math::basis> general_skeleton_basis_pair::get_basis() const
    {
        return basis_;
    }
}
