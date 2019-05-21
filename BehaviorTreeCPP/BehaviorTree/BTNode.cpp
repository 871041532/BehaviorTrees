


//			//-------------------------------------------------------------------------------------
//			// BevNodeLoop
//			//-------------------------------------------------------------------------------------
//			bool BevNodeLoop::_DoEvaluate(const BevNodeInputParam& input)
//			{
//				bool checkLoopCount = (mi_LoopCount == kInfiniteLoop) ||
//					mi_CurrentCount < mi_LoopCount;
//
//				if (!checkLoopCount)
//					return false;
//
//				if (_bCheckIndex(0))
//				{
//					BevNode* oBN = mao_ChildNodeList[0];
//					if (oBN->Evaluate(input))
//						return true;
//				}
//				return false;
//			}
//			void BevNodeLoop::_DoTransition(const BevNodeInputParam& input)
//			{
//				if (_bCheckIndex(0))
//				{
//					BevNode* oBN = mao_ChildNodeList[0];
//					oBN->Transition(input);
//				}
//				mi_CurrentCount = 0;
//			}
//			BevRunningStatus BevNodeLoop::_DoTick(const BevNodeInputParam& input, BevNodeOutputParam& output)
//			{
//				BevRunningStatus bIsFinish = k_BRS_Finish;
//				if (_bCheckIndex(0))
//				{
//					BevNode* oBN = mao_ChildNodeList[0];
//					bIsFinish = oBN->Tick(input, output);
//
//					if (bIsFinish == k_BRS_Finish)
//					{
//						if (mi_LoopCount != kInfiniteLoop)
//						{
//							mi_CurrentCount++;
//							if (mi_CurrentCount == mi_LoopCount)
//							{
//								bIsFinish = k_BRS_Executing;
//							}
//						}
//						else
//						{
//							bIsFinish = k_BRS_Executing;
//						}
//					}
//				}
//				if (bIsFinish)
//				{
//					mi_CurrentCount = 0;
//				}
//				return bIsFinish;
//			}
//		}
//	}
//}