//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "cs_base"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../src/mae/eventing/cs_base.cpp"


BOOST_AUTO_TEST_CASE( csbase )
{

    mae::eventing::cs_base csbase = mae::eventing::cs_base();

    std::string msg1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><maee:message xmlns:maee=\"http://www.example.org/maeeventing\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.example.org/maeeventing maeeventing.xsd\"><maee:type>short</maee:type>";
    std::string msg2 = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><maee:message xmlns:maee=\"http://www.example.org/maeeventing\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.example.org/maeeventing maeeventing.xsd\">"
                       "<maee:type>short</maee:type></maee:message>";

    BOOST_CHECK(!csbase.is_message_complete(msg1));
    BOOST_CHECK(csbase.is_message_complete(msg2));

}