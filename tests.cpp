#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sem4_coursework/Edmonds_Karp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	
	TEST_CLASS(exceptions_tests)
	{
	public:
		
		TEST_METHOD(no_input_file_exception)
		{
			Edmonds_Karp * testKarp;
			try
			{
				testKarp = new Edmonds_Karp("inpuut.txt");
			}
			catch (logic_error message)
			{
				Assert::AreEqual("No input file", message.what());
			}
		}
		TEST_METHOD(no_S_node_exception)
		{
			Edmonds_Karp * testKarp;
			try
			{
				testKarp = new Edmonds_Karp("input_without_S.txt");
			}
			catch (logic_error message)
			{
				Assert::AreEqual("No Source node", message.what());
			}
		}
		TEST_METHOD(no_T_node_exception)
		{
			Edmonds_Karp * testKarp;
			try
			{
				testKarp = new Edmonds_Karp("input_without_T.txt");
			}
			catch (logic_error message)
			{
				Assert::AreEqual("No Sink node", message.what());
			}
		}
		TEST_METHOD(no_way_to_sink_exception)
		{
			Edmonds_Karp * testKarp;
			try
			{
				testKarp = new Edmonds_Karp("input_without_way.txt");
			}
			catch (logic_error message)
			{
				Assert::AreEqual("No way to Sink", message.what());
			}
		}
	};

	TEST_CLASS(flow_tests)
	{
		TEST_METHOD(graph1)
		{
			Edmonds_Karp * testKarp = new Edmonds_Karp("input1.txt");
			Assert::IsTrue(testKarp->max_flow() == 5);
		}
		TEST_METHOD(graph2)
		{
			Edmonds_Karp * testKarp = new Edmonds_Karp("input2.txt");
			Assert::IsTrue(testKarp->max_flow() == 26);
		}
		TEST_METHOD(graph3)
		{
			Edmonds_Karp * testKarp = new Edmonds_Karp("input3.txt");
			Assert::IsTrue(testKarp->max_flow() == 21);
		}

	};
