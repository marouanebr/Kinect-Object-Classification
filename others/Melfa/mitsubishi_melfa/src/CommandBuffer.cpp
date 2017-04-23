// Source file of CommandBuffer class

#include <mitsubishi_melfa/CommandBuffer.hpp>

CommandBuffer::CommandBuffer(unsigned int uiBuffer_Length)
{
	m_uiBuffer_Length = uiBuffer_Length;
}

void CommandBuffer::pushNewCommand(mitsubishi_melfa::MelfaCommand NewMessage)
{
	m_queueBuffer.push(NewMessage);
	return;
}

mitsubishi_melfa::MelfaCommand CommandBuffer::popNextCommand()
{
	mitsubishi_melfa::MelfaCommand NextCommand;
	NextCommand = m_queueBuffer.front();
	m_queueBuffer.pop();
	return(NextCommand);
}

bool CommandBuffer::isBufferEmpty()
{
	bool bIsEmpty;
	bIsEmpty = m_queueBuffer.empty();
	return(bIsEmpty);
}

double CommandBuffer::getRemainingCapacity()
{	
	unsigned int uiNumElements = m_queueBuffer.size();
	double dRemainingCapacity = 1 - ( (double)uiNumElements / (double)m_uiBuffer_Length );
	return(dRemainingCapacity);
}

