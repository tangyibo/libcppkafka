#include <stdexcept>
#include <iostream>
#include "cppkafka/utils/buffered_producer.h"
#include "cppkafka/configuration.h"

using std::string;
using std::exception;
using std::getline;
using std::cin;
using std::cout;
using std::endl;

using cppkafka::BufferedProducer;
using cppkafka::Configuration;
using cppkafka::Topic;
using cppkafka::MessageBuilder;
using cppkafka::Message;

int main(int argc, char* argv[]) {
    string brokers="172.16.56.180:9092,172.16.56.118:9092";
    string topic_name="test_topic";
    int partition_value = -1;

    // Create a message builder for this topic
    MessageBuilder builder(topic_name);

    // Get the partition we want to write to. If no partition is provided, this will be
    // an unassigned one
    if (partition_value != -1) {
        builder.partition(partition_value);
    }

    // Construct the configuration
    Configuration config = {
        { "metadata.broker.list", brokers }
    };

    // Create the producer
    BufferedProducer<string> producer(config);

    // Set a produce success callback
    producer.set_produce_success_callback([](const Message& msg) {
        cout << "Successfully produced message with payload " << msg.get_payload() << endl;
    });
    // Set a produce failure callback
    producer.set_produce_failure_callback([](const Message& msg) {
        cout << "Failed to produce message with payload " << msg.get_payload() << endl;
        // Return false so we stop trying to produce this message
        return false;
    });

    cout << "Producing messages into topic " << topic_name << endl;

    // Now read lines and write them into kafka
    string line;
    while (getline(cin, line)) {
        // Set the payload on this builder
        builder.payload(line);

        // Add the message we've built to the buffered producer
        producer.add_message(builder);

        // Now flush so we:
        // * emit the buffered message
        // * poll the producer so we dispatch on delivery report callbacks and
        // therefore get the produce failure/success callbacks
        producer.flush();
    }
}
