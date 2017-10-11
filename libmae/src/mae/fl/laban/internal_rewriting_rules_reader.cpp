#include "internal_rewriting_rules_reader.hh"

//internal includes
#include "../../internal_mxml.hh"


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			internal_rewriting_rules_reader::internal_rewriting_rules_reader()
			{
				// TODO Auto-generated constructor stub

			}

			internal_rewriting_rules_reader::~internal_rewriting_rules_reader()
			{
				// TODO Auto-generated destructor stub
			}

			std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > internal_rewriting_rules_reader::read_rules_file(std::string file_name)
			{
				std::ifstream in_file(file_name);
				std::stringstream sstr;

				if (in_file.is_open())
				{
					std::string line;
					while (std::getline(in_file, line))
					{
						sstr << line << std::endl;
					}
					in_file.close();
					return read_rules_str(sstr.str());
				}

				return std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > >();
			}

			std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > internal_rewriting_rules_reader::read_rules_str(std::string xml_string)
			{
				std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > result;

				std::stringstream sstr;
				sstr << xml_string;

				xmlpp::DomParser parser;
				parser.parse_stream(sstr);

				xmlpp::Document* doc = parser.get_document();
				xmlpp::Node* root_node = doc->get_root_node();

				//setup namespace prefix
				std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map = std::shared_ptr<xmlpp::Node::PrefixNsMap>(new xmlpp::Node::PrefixNsMap());
				if (root_node->get_namespace_prefix().size() > 0)
				{
					namespace_map->insert(std::make_pair(root_node->get_namespace_prefix(), root_node->get_namespace_uri()));
				}

				std::string nsp = root_node->get_namespace_prefix();

				//---------------
				// main elements
				//---------------

				xmlpp::NodeSet movs_node_set = root_node->find(internal_mxml::get_xpath("rules/rule", nsp), *namespace_map);

				for (unsigned int i = 0; i < movs_node_set.size(); i++)
				{
					result.push_back(read_rule(movs_node_set.at(i), namespace_map, nsp));
				}

				return result;
			}

			std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > internal_rewriting_rules_reader::read_rule(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > result;


				//read sequence
				xmlpp::NodeSet seq_node_set = node->find(internal_mxml::get_xpath("sequence", nsp), *namespace_map);
				std::vector<std::shared_ptr<i_movement> > sequence;

				if (seq_node_set.size() > 0)
				{
					sequence = read_rule_sequence(seq_node_set.at(0), namespace_map, nsp);
				}
				else
				{
					return nullptr;
				}

				//read replacement
				xmlpp::NodeSet rep_node_set = node->find(internal_mxml::get_xpath("replacement", nsp), *namespace_map);
				std::vector<std::shared_ptr<i_movement> > replacement;

				if (rep_node_set.size() > 0)
				{
					replacement = read_rule_sequence(rep_node_set.at(0), namespace_map, nsp);
				}
				else
				{
					return nullptr;
				}


				std::shared_ptr<std::vector<std::vector<std::shared_ptr<i_movement> > > > replacements = std::shared_ptr<std::vector<std::vector<std::shared_ptr<i_movement> > > >(new std::vector<std::vector<std::shared_ptr<i_movement> > >());

				replacements->push_back(replacement);

				result = std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > >(new decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > >(sequence, replacements));

				return result;
			}

			std::vector<std::shared_ptr<i_movement> > internal_rewriting_rules_reader::read_rule_sequence(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::vector<std::shared_ptr<i_movement> > result;

				xmlpp::NodeSet seq_node_set = node->find(internal_mxml::get_xpath("element", nsp), *namespace_map);

				for (unsigned int i = 0; i < seq_node_set.size(); i++)
				{
					std::shared_ptr<i_movement> element = read_element(seq_node_set.at(i), namespace_map, nsp);

					if (element != nullptr)
					{
						result.push_back(element);
					}
				}

				return result;
			}

			std::shared_ptr<i_movement> internal_rewriting_rules_reader::read_element(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp)
			{
				std::shared_ptr<i_movement> result;

				mv::e_level vertical = mv::e_level_c::parse(internal_mxml::get_node_content(node, namespace_map, "vertical", nsp, "NONE"));
				mv::e_direction horizontal = mv::e_direction_c::parse(internal_mxml::get_node_content(node, namespace_map, "horizontal", nsp, "NONE"));
				bool hold = mbool::parse(internal_mxml::get_node_content(node, namespace_map, "hold", nsp, "false"));

				std::shared_ptr<mv::i_symbol> dir_sym = std::shared_ptr<mv::i_symbol>(new mv::direction_symbol(vertical, horizontal));

				result = std::shared_ptr<i_movement>(new movement( 0, 0, 0, 0, dir_sym, hold));

				return result;
			}



		} // namespace laban
	} // namespace fl
} // namespace mae
