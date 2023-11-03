#if !defined(COMMAND_QUEUE_H)
#define COMMAND_QUEUE_H

#include "Command.hpp"
#include <queue>

/**
 * @brief FIFO data structure(queue). This class serves as a wrapper around a queue of commands.
 *
 */
class CommandQueue : private sf::NonCopyable
{
public:
    CommandQueue() = default;
    void push(const Command &command);
    Command pop();
    size_t size() const {return queue.size(); }

    bool is_empty() const;
    ~CommandQueue() = default;

private:
    std::queue<Command> queue;
};

#endif // COMMAND_QUEUE_H
