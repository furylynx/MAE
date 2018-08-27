#include "prop.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				prop::prop(std::string name, std::string description)
				{
					name_ = name;
					description_ = description;

					if (name.size() == 0)
					{
						throw std::invalid_argument("A name must be defined.");
					}
				}

				prop::~prop()
				{

				}

				std::string prop::get_name() const
				{
					return name_;
				}

				std::string prop::get_description() const
				{
					return description_;
				}

				std::string prop::xml(unsigned int indent, std::string namesp) const
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
					sstr << indent_stream.str() << "<" << ns << "preSign>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "prop>" << std::endl;
					sstr << indent_stream.str() << "\t\t" << "<" << ns << "name>" << name_ << "</" << ns << "name>"
							<< std::endl;
					if (description_.size() > 0)
					{
						sstr << indent_stream.str() << "\t\t" << "<" << ns << "description>" << description_ << "</"
								<< ns << "description>" << std::endl;
					}
					sstr << indent_stream.str() << "\t" << "</" << ns << "prop>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "preSign>" << std::endl;

					return sstr.str();
				}

                std::string prop::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
                {
                    return svg(identifier, draw_rect(posx, posy, width, height), left);
                }

				std::string prop::svg(std::string identifier, draw_rect rect, bool left, svg_style style) const
				{
                    double posx = rect.get_posx();
                    double posy = rect.get_posy();
                    double width = rect.get_width();
                    double height = rect.get_height();

					std::stringstream sstr;

					sstr << "\t\t<rect" << std::endl;
					sstr << "\t\t\twidth=\"" << width <<  "\"" << std::endl;
					sstr << "\t\t\theight=\"" << height <<  "\"" << std::endl;
					sstr << "\t\t\tx=\"" << posx <<  "\"" << std::endl;
					sstr << "\t\t\ty=\"" << posy <<  "\"" << std::endl;
					sstr << "\t\t\tid=\"" << identifier << "\"" << std::endl;
					sstr << "\t\t\tstyle=\"";
					sstr << "fill:#" << style.get_fill_color() << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_stroke_width() << "pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none;";
					sstr << "\" />" << std::endl;


					//print line
					sstr << "<path" << std::endl;
					sstr << " d=\"m " << posx+width/2.0 << ","<< posy << "  " << 0 << "," << height/3.0 << "\"" << std::endl;
					sstr << "\t\t\tid=\"" << identifier << "-prop-line\"" << std::endl;
					sstr
							<< "\t\t\tstyle=\"fill:none;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\""
							<< std::endl;
					sstr << "\t\t\t/>" << std::endl;

					//print name
					sstr << "\t\t<text" << std::endl;
					sstr << "\t\tx=\"" << posx << "\"" << std::endl;
					sstr << "\t\ty=\"" << posy+2*height/3.0 << "\"" << std::endl;
					sstr << "\t\tid=\"" << identifier << "-prop-text\"" << std::endl;
					sstr << "\t\txml:space=\"preserve\"" << std::endl;
					sstr
							<< "\t\tstyle=\"font-size:11px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#" << style.get_text_color() << ";fill-opacity:1;stroke:none;font-family:Serif;-inkscape-font-specification:Serif\">"
							<< std::endl;
					sstr << name_ << std::endl;
					sstr << "\t\t</text>" << std::endl;

					return sstr.str();
				}

				bool prop::equals(std::shared_ptr<i_pre_sign> a) const
				{
					if (std::shared_ptr<prop> a_casted = std::dynamic_pointer_cast<prop>(a))
					{
						return (name_ == a_casted->get_name() && description_ == a_casted->get_description());
					}

					return false;
				}

				bool prop::all_types_equal(std::shared_ptr<i_pre_sign> a) const
				{
					if (std::shared_ptr<prop> a_casted = std::dynamic_pointer_cast<prop>(a))
					{
						return true;
					}

					return false;
				}

				std::vector<double> prop::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					result.push_back(hierarchy_factor * std::hash<std::string>()(name_) / (double)std::numeric_limits<std::size_t>::max());
					result.push_back(hierarchy_factor * std::hash<std::string>()(description_) / (double)std::numeric_limits<std::size_t>::max());

					return result;
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
