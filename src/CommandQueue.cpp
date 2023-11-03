#include "CommandQueue.hpp"

void CommandQueue::push(const Command &command)
{
    queue.push(command);
}

Command CommandQueue::pop()
{
    Command command = queue.front();
    queue.pop();
    return command;
}

bool CommandQueue::is_empty() const
{
    return queue.empty();
}