#include "testSorter.h"
#include "Lithe/LitheCore.h"
using namespace lithe;

SorterTest::SorterTest(void) {}

SorterTest::~SorterTest(void) {}

void SorterTest::SetUp(void) {}

void SorterTest::TearDown(void) {}

TEST_F(SorterTest, BFS_SimpleTest)
{
	// [n3]->[n2]->[n1]->[sink]

	Sink sink(1);
	Node n1(1, 1);
	Patcher::connect(sink.getInlet(), n1.getOutlet());
	Node n2(1, 1);
	Patcher::connect(n1.getInlet(), n2.getOutlet());
	Node n3(1, 1);
	Patcher::connect(n2.getInlet(), n3.getOutlet());

	BFS::sort(sink);

	EXPECT_FALSE( sink.getInlet().sampleDelayEnabled() );
	EXPECT_FALSE( n1.getInlet().sampleDelayEnabled() );
	EXPECT_FALSE( n2.getInlet().sampleDelayEnabled() );
	EXPECT_FALSE( n3.getInlet().sampleDelayEnabled() );

}

TEST_F(SorterTest, BFS_FeedbackTest)
{
	//   |-----------
	//   v           |
	// [n3]->[n2]->[n1]->[sink]

	Sink sink(1);
	Node n1(1, 1);
	Patcher::connect(sink.getInlet(), n1.getOutlet());
	Node n2(1, 1);
	Patcher::connect(n1.getInlet(), n2.getOutlet());
	Node n3(1, 1);
	Patcher::connect(n2.getInlet(), n3.getOutlet());
	Patcher::connect(n3.getInlet(), n1.getOutlet());
	BFS::sort(sink);

	EXPECT_FALSE( sink.getInlet().sampleDelayEnabled() );
	EXPECT_FALSE( n1.getInlet().sampleDelayEnabled() );
	EXPECT_FALSE( n2.getInlet().sampleDelayEnabled() );
	EXPECT_TRUE( n3.getInlet().sampleDelayEnabled() );
}


TEST_F(SorterTest, BFS_DoubleFeedbackTest)
{
	// A more complicated graph with two inlets being feed by feedback paths (F and C)

	Sink sink(1);

	Node B(2, 1);
	Node E(2, 1);
	Node F(1, 1);
	Node C(1, 1);
	Node D(0, 1);

	Patcher::connect(sink.getInlet(0), B.getOutlet(0));
	Patcher::connect(B.getInlet(1), D.getOutlet(0));
	Patcher::connect(B.getInlet(0), E.getOutlet(0));
	Patcher::connect(C.getInlet(0), B.getOutlet(0));
	Patcher::connect(E.getInlet(1), C.getOutlet(0));
	Patcher::connect(E.getInlet(0), F.getOutlet(0));
	Patcher::connect(F.getInlet(0), C.getOutlet(0));

	BFS::sort(sink);

	EXPECT_FALSE( sink.getInlet(0).sampleDelayEnabled() );
	EXPECT_FALSE( B.getInlet(0).sampleDelayEnabled() );
	EXPECT_FALSE( B.getInlet(1).sampleDelayEnabled() );
	EXPECT_TRUE( C.getInlet(0).sampleDelayEnabled() );
	EXPECT_FALSE( E.getInlet(0).sampleDelayEnabled() );
	EXPECT_FALSE( E.getInlet(1).sampleDelayEnabled() );
	EXPECT_TRUE( F.getInlet(0).sampleDelayEnabled() );
}

TEST_F(SorterTest, BFS_DoubleFeedbackTest_Sink2)
{
	// Same as BFS_DoubleFeedbackTest with two sink inputs

	Sink sink(2);

	Node B(2, 1);
	Node E(2, 1);
	Node F(1, 1);
	Node C(1, 1);
	Node D(0, 1);

	Patcher::connect(sink.getInlet(1), B.getOutlet(0));
	Patcher::connect(B.getInlet(1), D.getOutlet(0));
	Patcher::connect(B.getInlet(0), E.getOutlet(0));
	Patcher::connect(C.getInlet(0), B.getOutlet(0));
	Patcher::connect(E.getInlet(1), C.getOutlet(0));
	Patcher::connect(E.getInlet(0), F.getOutlet(0));
	Patcher::connect(sink.getInlet(0), F.getOutlet(0));

	BFS::sort(sink);

	EXPECT_FALSE( sink.getInlet(0).sampleDelayEnabled() );
	EXPECT_FALSE( B.getInlet(0).sampleDelayEnabled() );
	EXPECT_FALSE( B.getInlet(1).sampleDelayEnabled() );
	EXPECT_TRUE( C.getInlet(0).sampleDelayEnabled() );
	EXPECT_TRUE( E.getInlet(0).sampleDelayEnabled() );
	EXPECT_FALSE( E.getInlet(1).sampleDelayEnabled() );
	EXPECT_FALSE( F.getInlet(0).sampleDelayEnabled() );

	// DEBUG PRINTING
	// cout << "sink   " << sink.index << "  " << ( sink.getInlet().sampleDelayEnabled() ? "Delay" : " ") << endl << endl;
	// cout << "B   " << B.index << "  " << ( B.getInlet().sampleDelayEnabled() || B.getInlet(1).sampleDelayEnabled() ? "Delay" : " ") << endl << endl;
	// cout << "D   " << D.index << "  " << endl;
	// cout << "E   " << E.index << "  " << ( E.getInlet().sampleDelayEnabled() || E.getInlet(1).sampleDelayEnabled() ? "Delay" : " ") << endl << endl;
	// cout << "F   " << F.index << "  " << ( F.getInlet().sampleDelayEnabled() ? "Delay" : " ") << endl ;
	// cout << "C   " << C.index << "  " << ( C.getInlet().sampleDelayEnabled() ? "Delay" : " ") << endl ;
}