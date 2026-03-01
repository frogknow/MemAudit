#include "CircQueue.h"

bool CircQueue::Push(const MembType& memb)
{
	int nextIdx = mQueueCtrl.NextIndex();
	if(nextIdx >= 0) {
		mQueueMembs[nextIdx] = memb;
		mQueueCtrl.StepForward(1);
		return true;
	}

	return false;
}

void CircQueue::Pop()
{
	mQueueCtrl.PopRear();
}


bool CircQueue::Empty() const
{
	return mQueueCtrl.IsEmpty();
}

int  CircQueue::Size() const
{
	return mQueueCtrl.GetCurNum();
}

const MembType& CircQueue::Front() const
{
	int idx = mQueueCtrl.RearIndex();
	if(idx >= 0) {
		return mQueueMembs[idx];
	}

	return mQueueMembs[-1];
}

const MembType& CircQueue::Back() const
{
	if(Size() > 0) {
		int idx = mQueueCtrl.GetCurPos();
		if(idx >= 0) {
			return mQueueMembs[idx];
		}
	}

	return mQueueMembs[-1];
}


