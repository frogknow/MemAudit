#ifndef __CIRC_QUEUE_H__
#define __CIRC_QUEUE_H__


class CircQueueCtrlData
{
public:
	bool Init(int cqSize, bool autoDrop)
	{
		mCurNum = 0;
		mCurPos = 0;
		mMaxNum = cqSize;
		mAutoDrop = autoDrop;
		return true;
	}

	bool IsEmpty() const
	{
		return (mCurNum == 0);
	}

	int GetCurNum() const
	{
		return mCurNum;
	}

	int GetMaxNum() const
	{
		return mMaxNum;
	}

	int GetCurPos() const
	{
		return mCurPos;
	}

	int RearIndex() const
	{
		if(! IsEmpty()) {
			int rear = (mCurPos - mCurNum + 1);
			if(rear < 0) {
				rear += mMaxNum;
			}
			return rear;
		} else {
			return -1;
		}
	}

	int NextIndex() const
	{
		if(mCurNum >= mMaxNum && ! mAutoDrop) {
			return -1;
		}

		int idx = mCurPos + 1;
		idx %= mMaxNum;
		return idx;
	}

	void StepForward(int num)
	{
		if(num <= 0) {
			return;
		}

		if(num == 1) {
			mCurPos += 1;
			mCurPos %= mMaxNum;
			if(mCurNum < mMaxNum) {
				++mCurNum;
			}
			return;
		}

		num %= mMaxNum;
		if(num == 0) {
			mCurNum = mMaxNum;
			return;
		}


		while(num-- > 0) {
			StepForward(1);
		}
	}

#if 0
	void StepBack(int num)
	{
		if(num <= 0) {
			return;
		}

		if(num == 1) {
			mCurPos -= 1;
			if(mCurPos < 0) {
				mCurPos += mMaxNum;
			}

			if(mCurNum > 0) {
				--mCurNum;
			}

			return;
		}

		num %= mMaxNum;
		if(num == 0) {
			mCurNum = 0;
			return;
		}

		while(num-- > 0) {
			StepBack(1);
		}
	}
#endif

	void PopRear()
	{
		if(mCurNum > 0) {
			--mCurNum;
		}
	}


	bool GetAll(vector<int>& allIdx) const
	{
		if(IsEmpty()) {
			return false;
		}

		int curNum = GetCurNum();
		allIdx.resize(curNum);
		int rearIdx = RearIndex();
		for(int idx = 0; idx < curNum; ++idx) {
			int lqIdx = rearIdx + idx;
			lqIdx %= mMaxNum;
			allIdx[idx] = lqIdx;
		}

		return true;
	}


private:
	int mMaxNum = 0;
	int mCurNum = 0;
	int mCurPos = 0; // the pos of the lastest data
	bool mAutoDrop = false;
};


template<typename MembType, int queueSize, bool dropIfFull>
class CircQueue
{
	CircQueue()
	{
		mQueueCtrl.Init(queueSize, dropIfFull);
	}

	bool Push(const MembType& memb);
	void Pop();

	bool Empty() const;
	int  Size() const;

	const MembType& Front() const;
	const MembType& Back() const;


private:
	MembType mQueueMembs[queueSize];
	CircQueueCtrlData mQueueCtrl;
};


#endif
