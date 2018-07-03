#include <stdexcept>
#include <iostream>
#include "cppkafka/producer.h"
#include "cppkafka/configuration.h"
#include "cppkafka/metadata.h"
#include "cppkafka/topic.h"

using std::string;
using std::exception;
using std::cout;
using std::endl;

using cppkafka::Producer;
using cppkafka::Exception;
using cppkafka::Configuration;
using cppkafka::Topic;
using cppkafka::Metadata;
using cppkafka::TopicMetadata;
using cppkafka::BrokerMetadata;

int main(int argc, char* argv[]) {
    string brokers="172.16.56.180:9092,172.16.56.118:9092";

    // Construct the configuration
    Configuration config = {
        { "metadata.broker.list", brokers },
    };

    try {
        // Construct a producer
        Producer producer(config);

        // Fetch the metadata
        Metadata metadata = producer.get_metadata();

        // Iterate over brokers
        cout << "Found the following brokers: " << endl;
        for (const BrokerMetadata& broker : metadata.get_brokers()) {
            cout << "* " << broker.get_host() << endl;
        }
        cout << endl;

        // Iterate over topics
        cout << "Found the following topics: " << endl;
        for (const TopicMetadata& topic : metadata.get_topics()) {
            cout << "* " << topic.get_name() << ": " << topic.get_partitions().size()
                 << " partitions" << endl;
        }
    }
    catch (const Exception& ex) {
        cout << "Error fetching metadata: " << ex.what() << endl;
    }
}
