#include "digit_part.hpp"

namespace mae
{
    namespace fl
    {
        namespace laban
        {
            namespace ps
            {

                digit_part::digit_part(e_digit digit, unsigned int knuckle)
                {
                    digit_ = digit;
                    knuckle_ = knuckle;

                    if (digit == e_digit::INDEXFINGER || digit == e_digit::LITTLEFINGER
                        || digit == e_digit::MIDDLEFINGER || digit == e_digit::RINGFINGER
                        || digit == e_digit::THUMB)
                    {
                        if (knuckle > 4)
                        {
                            throw std::invalid_argument(
                                    "Knuckle must not be greater than 4 since a finger is addressed.");
                        }
                    }
                    else if (digit == e_digit::NONE_DIGIT)
                    {
                        throw std::invalid_argument("Digit is set to NONE which is invalid.");
                    }
                    else
                    {
                        if (knuckle > 3)
                        {
                            throw std::invalid_argument("Knuckle must not be greater than 3 since a toe is addressed.");
                        }
                    }
                }

                digit_part::~digit_part()
                {
                }

                e_digit digit_part::get_digit() const
                {
                    return digit_;
                }

                unsigned int digit_part::get_knuckle() const
                {
                    return knuckle_;
                }

                std::string digit_part::xml(unsigned int indent, std::string namesp) const
                {
                    std::stringstream indent_stream;

                    for (unsigned int i = 0; i < indent; i++)
                    {
                        indent_stream << "\t";
                    }

                    std::string ns = namesp;
                    if (ns.size() > 0 && ns.at(ns.size() - 1) != ':')
                    {
                        ns.push_back(':');
                    }

                    std::stringstream sstr;

                    //print definition
                    sstr << indent_stream.str() << "<" << ns << "digit>" << std::endl;

                    //print digit
                    sstr << indent_stream.str() << "\t" << "<" << ns << "digit>" << e_digit_c::str(digit_) << "</" << ns
                         << "digit>" << std::endl;

                    //print joint
                    sstr << indent_stream.str() << "\t" << "<" << ns << "joint>" << knuckle_ << "</" << ns << "joint>"
                         << std::endl;

                    sstr << indent_stream.str() << "</" << ns << "digit>" << std::endl;

                    return sstr.str();
                }

                std::string digit_part::svg(std::string identifier, double posx, double posy, double width,
                                            double height, bool left) const
                {
                    identifier.append("digit-part");
                    identifier.append(e_digit_c::str(digit_));

                    if (width > height)
                    {
                        posx += width-height;
                        width = height;
                    }
                    else
                    {
                        height = width;
                    }

                    if (digit_ == e_digit::THUMB || digit_ == e_digit::INDEXFINGER || digit_ == e_digit::MIDDLEFINGER || digit_ == e_digit::RINGFINGER || digit_ == e_digit::LITTLEFINGER)
                    {
                        return svg_for_finger(identifier, posx, posy, width, height, left);
                    }
                    else
                    {
                        return svg_for_toe(identifier, posx, posy, width, height, left);
                    }
                }

                int digit_part::get_digit_increment() const
                {
                    int digit_increment = 0;

                    if (digit_ == e_digit::THUMB)
                    {
                    }
                    else if (digit_ == e_digit::INDEXFINGER)
                    {
                        digit_increment = 1;
                    }
                    else if (digit_ == e_digit::MIDDLEFINGER)
                    {
                        digit_increment = 2;
                    }
                    else if (digit_ == e_digit::RINGFINGER)
                    {
                        digit_increment = 3;
                    }
                    else if (digit_ == e_digit::LITTLEFINGER)
                    {
                        digit_increment = 4;
                    }
                    else if (digit_ == e_digit::BIGTOE)
                    {

                    }
                    else if (digit_ == e_digit::LONGTOE)
                    {
                        digit_increment = 1;
                    }
                    else if (digit_ == e_digit::MIDDLETOE)
                    {
                        digit_increment = 2;
                    }
                    else if (digit_ == e_digit::RINGTOE)
                    {
                        digit_increment = 3;
                    }
                    else if (digit_ == e_digit::LITTLETOE)
                    {
                        digit_increment = 4;
                    }
                    return digit_increment;
                }

                std::string digit_part::svg_for_finger(const std::string &identifier, double posx, double posy, double width, double height,
                                           bool left) const
                {

                    double radius = height / 16.0;
                    double mirrorpos = 2 * posx + width;

                    int digit_increment = get_digit_increment();

                    std::stringstream sstr;

                    sstr << "<path" << std::endl;

                    sstr << "d=\"m " << posx << "," << posy << " " << 0 << "," << 3.0 * height / 4.0 <<
                         "  m  " << width << "," << -2 * height / 4.0 << " " << -3 * width / 4.0 << "," << -height / 4.0
                         << "  " << 0 << "," << 3 * height / 4.0 << " " << 3 * width / 4.0 << "," << height / 4.0
                         << " m " << 0 << "," << -3 * height / 16.0 << " " << -3 * width / 4.0 << "," << -height / 4.0
                         << " m " << 0 << "," << -3 * height / 16.0 << " " << 3 * width / 4.0 << "," << height / 4.0
                         << " m " << 0 << "," << -3 * height / 16.0 << " " << -3 * width / 4.0 << "," << -height / 4.0;

                    sstr << "\"" << std::endl;


                    if (left)
                    {
                        //mirror for left hand
                        sstr << "transform=\"matrix(-1,0,0,1," << mirrorpos << ",0)\"" << std::endl;
                    }

                    sstr << "\t\t\tid=\"" << identifier << "\"" << std::endl;
                    sstr
                            << "\t\t\tstyle=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\""
                            << std::endl;
                    sstr << "\t\t\t/>" << std::endl;

                    //set dots for knuckles/phalanges
                    if (knuckle_ == 0 || knuckle_ >= 3)
                    {
                        std::stringstream idsstr;
                        idsstr << identifier << "-dot-base";

                        sstr << svg_str_dot(idsstr.str(), posx + width, posy + (height / 4.0) + (digit_increment * 3 * height / 16.0), radius, left, mirrorpos);
                    }

                    if (knuckle_ >= 1)
                    {
                        std::stringstream idsstr;
                        idsstr << identifier << "-dot-end";

                        sstr << svg_str_dot(idsstr.str(), posx + (width / 4.0), posy + (digit_increment * 3 * height / 16.0), radius, left, mirrorpos);
                    }

                    if (knuckle_ == 3 || knuckle_ == 2)
                    {
                        std::stringstream idsstr;
                        idsstr << identifier << "-dot-mid";
                        sstr << svg_str_dot(idsstr.str(), posx + (5 * width / 8.0), posy + (digit_increment * 3 * height / 16.0) + height / 8.0, radius, left, mirrorpos);
                    }
                    else if (knuckle_ == 4)
                    {
                        std::stringstream idsstr;
                        idsstr << identifier << "-dot-base";

                        sstr << svg_str_dot(idsstr.str(), posx + (2 * width / 4.0), posy + (digit_increment * 3 * height / 16.0) + height / 12.0, radius, left, mirrorpos);

                        idsstr << "-p2";
                        sstr << svg_str_dot(idsstr.str(), posx + (3 * width / 4.0), posy + (digit_increment * 3 * height / 16.0) + height / 6.0, radius, left, mirrorpos);
                    }

                    return sstr.str();
                }

                std::string
                digit_part::svg_for_toe(const std::string &identifier, double posx, double posy, double width, double height,
                                        bool left) const
                {

                    double radius = height / 16.0;
                    double mirrorpos = 2 * posx + width;

                    int digit_increment = get_digit_increment();

                    std::stringstream sstr;

                    sstr << "<path" << std::endl;

                    sstr << "d=\"m " << posx << "," << posy << " " << 0 << "," << height
                         << " m " << width/4.0 << "," << 0 << " " << 0 << "," << -height
                         << " m " << 0 << "," << height / 6.0 << " " << 3 * width / 4.0 << "," << 0
                         << " m " << -3*width/4.0 << "," << height / 6.0 << " " << 3 * width / 4.0 << "," << 0
                         << " m " << -3*width/4.0 << "," << height / 6.0 << " " << 3 * width / 4.0 << "," << 0
                         << " m " << -3*width/4.0 << "," << height / 6.0 << " " << 3 * width / 4.0 << "," << 0
                         << " m " << -3*width/4.0 << "," << height / 6.0 << " " << 3 * width / 4.0 << "," << 0;

                    sstr << "\"" << std::endl;


                    if (left)
                    {
                        //mirror for left hand
                        sstr << "transform=\"matrix(-1,0,0,1," << mirrorpos << ",0)\"" << std::endl;
                    }

                    sstr << "\t\t\tid=\"" << identifier << "\"" << std::endl;
                    sstr
                            << "\t\t\tstyle=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\""
                            << std::endl;
                    sstr << "\t\t\t/>" << std::endl;


                    //set dots for knuckles/phalanges
                    if (knuckle_ == 0 || knuckle_ >= 3)
                    {
                        std::stringstream idsstr;
                        idsstr << identifier << "-dot-base";

                        sstr << svg_str_dot(idsstr.str(), posx + width, posy + (height / 6.0) + (digit_increment * height / 6.0), radius, left, mirrorpos);
                    }

                    if (knuckle_ >= 1)
                    {
                        std::stringstream idsstr;
                        idsstr << identifier << "-dot-end";

                        sstr << svg_str_dot(idsstr.str(), posx + (width / 4.0), posy + (height / 6.0) + (digit_increment * height / 6.0), radius, left, mirrorpos);
                    }

                    if (knuckle_ == 3 || knuckle_ == 2)
                    {
                        std::stringstream idsstr;
                        idsstr << identifier << "-dot-mid";
                        sstr << svg_str_dot(idsstr.str(), posx + (5 * width / 8.0), posy + (height / 6.0) + (digit_increment * height / 6.0), radius, left, mirrorpos);
                    }
                    else if (knuckle_ == 4)
                    {
                        std::stringstream idsstr;
                        idsstr << identifier << "-dot-base";

                        sstr << svg_str_dot(idsstr.str(), posx + (2 * width / 4.0), posy + (height / 6.0)  + (digit_increment * height / 6.0), radius, left, mirrorpos);

                        idsstr << "-p2";
                        sstr << svg_str_dot(idsstr.str(), posx + (3 * width / 4.0), posy + (height / 6.0)  + (digit_increment * height / 6.0), radius, left, mirrorpos);
                    }

                    return sstr.str();
                }

                std::shared_ptr<i_endpoint> digit_part::get_fixed_end() const
                {
                    if (knuckle_ == 0)
                    {
                        if (digit_ == e_digit::INDEXFINGER || digit_ == e_digit::LITTLEFINGER
                            || digit_ == e_digit::MIDDLEFINGER || digit_ == e_digit::RINGFINGER
                            || digit_ == e_digit::THUMB)
                        {
                            return std::shared_ptr<i_endpoint>(new joint_part(e_joint::HAND));
                        }
                        else
                        {
                            return std::shared_ptr<i_endpoint>(new joint_part(e_joint::FOOT));
                        }
                    }
                    else
                    {
                        return std::shared_ptr<i_endpoint>(new digit_part(digit_, knuckle_-1));
                    }
                }

                bool digit_part::equals(std::shared_ptr<i_endpoint> a) const
                {
                    if (std::shared_ptr<digit_part> a_casted = std::dynamic_pointer_cast<digit_part>(a))
                    {
                        return (digit_ == a_casted->get_digit() && knuckle_ == a_casted->get_knuckle());
                    }

                    return false;
                }

                bool digit_part::equals(std::shared_ptr<i_part> a) const
                {
                    if (std::shared_ptr<i_endpoint> a_casted = std::dynamic_pointer_cast<i_endpoint>(a))
                    {
                        return equals(a_casted);
                    }

                    return false;
                }

                bool digit_part::all_types_equal(std::shared_ptr<i_endpoint> a) const
                {
                    if (std::shared_ptr<digit_part> a_casted = std::dynamic_pointer_cast<digit_part>(a))
                    {
                        return true;
                    }

                    return false;
                }

                bool digit_part::all_types_equal(std::shared_ptr<i_part> a) const
                {
                    if (std::shared_ptr<i_endpoint> a_casted = std::dynamic_pointer_cast<i_endpoint>(a))
                    {
                        return all_types_equal(a_casted);
                    }

                    return false;
                }

                std::vector<double> digit_part::feature_vector() const
                {
                    std::vector<double> result;

                    result.push_back(e_digit_c::to_int(digit_));
                    result.push_back(knuckle_);

                    return result;
                }

                std::string digit_part::svg_str_dot(std::string identifier, double centerx, double centery, double radius, bool left, double mirrorpos) const
                {
                    std::stringstream sstr;

                    //draw circle
                    sstr << "<path" << std::endl;

                    sstr << "d=\"m " << centerx + radius << "," << centery << " a "
                         << radius << "," << radius << " 0 1 1 -" << 2 * radius << ",0 " << radius << ","
                         << radius << " 0 1 1 " << 2 * radius << ",0 z"
                         << " m " << -radius << "," << 0 ;

                    sstr << "\"" << std::endl;

                    if (left)
                    {
                        //mirror for left hand
                        sstr << "transform=\"matrix(-1,0,0,1," << mirrorpos << ",0)\"" << std::endl;
                    }

                    sstr << "\t\t\tid=\"" << identifier << "\"" << std::endl;
                    sstr
                            << "\t\t\tstyle=\"fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\""
                            << std::endl;
                    sstr << "\t\t\t/>" << std::endl;

                    return sstr.str();
                }

            } // namespace ps
        } // namespace laban
    } // namespace fl
} // namespace mae
