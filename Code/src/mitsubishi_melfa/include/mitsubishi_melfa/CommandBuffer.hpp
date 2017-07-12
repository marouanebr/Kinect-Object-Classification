// Header of melfa communication class
#ifndef COMMANDBUFFER_HPP
#define COMMANDBUFFER_HPP

#include <queue>
#include <mitsubishi_melfa/MelfaCommand.h>


/**
 *  This class is used by the communication node to store
 * unprocessed commands. It utilizes an stl::queue as underlying
 * container.
 */

class  CommandBuffer
{
  private:
    /**
         * @brief m_uiBuffer_Length Member variable determining the maximal size of the buffer
         */
  	unsigned int m_uiBuffer_Length;

        /**
         * @brief m_queueBuffer Member variable storing the unprocessed commands (stl::queue)
         */
  	std::queue<mitsubishi_melfa::MelfaCommand> m_queueBuffer;

  public:
        /**
         * @brief The constructor of the CommandoBuffer class.
         * @param uiBuffer_Length unsigned integer argument.
         */
        CommandBuffer(unsigned int uiBuffer_Length);

        /**
         * @brief Member function to save a new command to the buffer.
         * @param MelfaCommand customized ROS message: MelfaCommand.
         */
  	void pushNewCommand(mitsubishi_melfa::MelfaCommand);

        /**
         * @brief Member function to extract the next waiting command from the front
         * of the queue.
         * @return customized ROS message: MelfaCommand.
         */
  	mitsubishi_melfa::MelfaCommand popNextCommand();

        /**
         * @brief Member function to check whether the buffer is empty
         * @return boolean
         */
  	bool isBufferEmpty();

        /**
         * @brief  Member function to check the remaining capacitiy of the container
         * @return double
         */
  	double getRemainingCapacity();
};

#endif
