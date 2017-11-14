//
// Created by keks on 14.11.17.
//

#include "mahalanobis_distance.hpp"

#include <opencv2/opencv.hpp>

namespace mae
{
    namespace math
    {
        mahalanobis_distance::mahalanobis_distance()
        {

        }

        mahalanobis_distance::~mahalanobis_distance()
        {

        }

        double mahalanobis_distance::distance(std::vector<double> element1, std::vector<double> element2) const
        {
            cv::InputArray v1(element1);
            cv::InputArray v2(element2);


            cv::Mat observations;

            cv::hconcat(v1,v2, observations);

            cv::Mat mean, covs;
            cv::calcCovarMatrix(observations, covs, mean, CV_COVAR_NORMAL | CV_COVAR_ROWS | CV_COVAR_SCALE);
            cv::InputArray icovar = covs.inv();

            return cv::Mahalanobis(v1, v2, icovar);
        }

    }

}