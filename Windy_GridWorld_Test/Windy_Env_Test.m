//
//  Windy_Env_Test.m
//  Windy_GridWorld_Test
//
//  Created by Xiaoyue Ding on 9/27/21.
//

#import <XCTest/XCTest.h>
#import "GridWorld.hpp"
#import "WindyEnv.hpp"


@interface Windy_Env_Test : XCTestCase {
@private
    gridWorld* testWorld;
    windyEnv* testEnv;
}

@end

@implementation Windy_Env_Test

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
    vector_2D testGrid (7, std::vector<int> {0, 0, 0, 1, 1, 1, 2, 2, 1, 0});
    std::tuple<int, int> testStart {3, 0};
    std::tuple<int, int> testGoal {3, 7};
    
    testWorld = new gridWorld(testGrid, testStart, testGoal);
    testEnv = new windyEnv(*testWorld);
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    delete testEnv;
    testEnv = nullptr;
    delete testWorld;
    testWorld = nullptr;
    
}

- (void)testAvailableCrossMoves {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    std::vector<std::tuple<int, int>> testMoves;
    
    std::tuple<int, int> testPos_1 {0, 0};
    testMoves = testEnv->availableCrossMoves(testPos_1);
    XCTAssertEqual(2, static_cast<int>(testMoves.size()));
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(1,0)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(0,1)) != testMoves.end());
    
    std::tuple<int, int> testPos_2 {3, 1};
    testMoves = testEnv->availableCrossMoves(testPos_2);
    XCTAssertEqual(4, static_cast<int>(testMoves.size()));
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(1,0)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(0,1)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(-1,0)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(0,-1)) != testMoves.end());
}

- (void)testAvailableKingMoves {
    std::vector<std::tuple<int, int>> testMoves;
    
    std::tuple<int, int> testPos_1 {0, 0};
    testMoves = testEnv->availableKingMoves(testPos_1);
    XCTAssertEqual(3, static_cast<int>(testMoves.size()));
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(1,0)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(0,1)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(1,1)) != testMoves.end());
    
    std::tuple<int, int> testPos_2 {3, 1};
    testMoves = testEnv->availableKingMoves(testPos_2);
    XCTAssertEqual(8, static_cast<int>(testMoves.size()));
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(1,0)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(0,1)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(-1,0)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(0,-1)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(1,1)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(1,-1)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(-1,1)) != testMoves.end());
    XCTAssertTrue(std::find(testMoves.begin(), testMoves.end(), std::make_tuple(-1,-1)) != testMoves.end());
}

- (void)testGetSteadyWindResp {
    std::tuple<int, int> testPos_3 {2, 8};
    std::tuple<int, int> testMove_31 {1, 0};
    std::tuple<int, int> testMove_32 {0, 1};
    std::tuple<int, int> testMove_33 {-1, 0};
    std::tuple<int, int> testMove_34 {0, -1};
    
    windyResponse testResponse;
    
    testResponse = testEnv->getSteadyWindResp(testPos_3, testMove_31);
    XCTAssertEqual(std::make_tuple(4, 8), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
    testResponse = testEnv->getSteadyWindResp(testPos_3, testMove_32);
    XCTAssertEqual(std::make_tuple(3, 9), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
    testResponse = testEnv->getSteadyWindResp(testPos_3, testMove_33);
    XCTAssertEqual(std::make_tuple(2, 8), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
    testResponse = testEnv->getSteadyWindResp(testPos_3, testMove_34);
    XCTAssertEqual(std::make_tuple(3, 7), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertTrue(testResponse.finished);
    
    std::tuple<int, int> testPos_4 {3, 2};
    std::tuple<int, int> testMove_41 {1, 0};
    std::tuple<int, int> testMove_42 {0, 1};
    std::tuple<int, int> testMove_43 {-1, 0};
    std::tuple<int, int> testMove_44 {0, -1};
    
    testResponse = testEnv->getSteadyWindResp(testPos_4, testMove_41);
    XCTAssertEqual(std::make_tuple(4, 2), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
    testResponse = testEnv->getSteadyWindResp(testPos_4, testMove_42);
    XCTAssertEqual(std::make_tuple(3, 3), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
    testResponse = testEnv->getSteadyWindResp(testPos_4, testMove_43);
    XCTAssertEqual(std::make_tuple(2, 2), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
    testResponse = testEnv->getSteadyWindResp(testPos_4, testMove_44);
    XCTAssertEqual(std::make_tuple(3, 1), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
}

- (void)testGetStochasticWindResp {
    std::tuple<int, int> testPos_5 {3, 2};
    std::tuple<int, int> testMove_51 {1, 0};
    std::tuple<int, int> testMove_52 {0, 1};
    std::tuple<int, int> testMove_53 {-1, 0};
    std::tuple<int, int> testMove_54 {0, -1};
    
    windyResponse testResponse;
    
    testResponse = testEnv->getSteadyWindResp(testPos_5, testMove_51);
    XCTAssertEqual(std::make_tuple(4, 2), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
    testResponse = testEnv->getSteadyWindResp(testPos_5, testMove_52);
    XCTAssertEqual(std::make_tuple(3, 3), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
    testResponse = testEnv->getSteadyWindResp(testPos_5, testMove_53);
    XCTAssertEqual(std::make_tuple(2, 2), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
    testResponse = testEnv->getSteadyWindResp(testPos_5, testMove_54);
    XCTAssertEqual(std::make_tuple(3, 1), testResponse.next_state);
    XCTAssertEqual(-1, testResponse.reward);
    XCTAssertFalse(testResponse.finished);
    
    std::tuple<int, int> testPos_6 {2, 8};
    std::tuple<int, int> testMove_61 {1, 0};
    std::tuple<int, int> testMove_62 {0, 1};
    std::tuple<int, int> testMove_63 {-1, 0};
    std::tuple<int, int> testMove_64 {0, -1};
    
    std::vector<std::tuple<int, int>> testRespPos;
    
    for (int i (0); i<100; ++i) {
        testResponse = testEnv->getStochasticWindResp(testPos_6, testMove_61);
        testRespPos.push_back(testResponse.next_state);
        XCTAssertEqual(-1, testResponse.reward);
        XCTAssertFalse(testResponse.finished);
    }
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(3, 8)) != testRespPos.end());
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(4, 8)) != testRespPos.end());
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(5, 8)) != testRespPos.end());
    
    for (int i (0); i<100; ++i) {
        testResponse = testEnv->getStochasticWindResp(testPos_6, testMove_62);
        testRespPos.push_back(testResponse.next_state);
        XCTAssertEqual(-1, testResponse.reward);
        XCTAssertFalse(testResponse.finished);
    }
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(2, 9)) != testRespPos.end());
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(3, 9)) != testRespPos.end());
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(4, 9)) != testRespPos.end());
    
    for (int i (0); i<100; ++i) {
        testResponse = testEnv->getStochasticWindResp(testPos_6, testMove_63);
        testRespPos.push_back(testResponse.next_state);
        XCTAssertEqual(-1, testResponse.reward);
        XCTAssertFalse(testResponse.finished);
    }
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(1, 8)) != testRespPos.end());
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(2, 8)) != testRespPos.end());
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(3, 8)) != testRespPos.end());
    
    for (int i (0); i<100; ++i) {
        testResponse = testEnv->getStochasticWindResp(testPos_6, testMove_64);
        testRespPos.push_back(testResponse.next_state);
        XCTAssertEqual(-1, testResponse.reward);
        XCTAssertEqual(testResponse.next_state == testWorld->getGoal(), testResponse.finished);
    }
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(2, 7)) != testRespPos.end());
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(3, 7)) != testRespPos.end());
    XCTAssertTrue(std::find(testRespPos.begin(), testRespPos.end(), std::make_tuple(4, 7)) != testRespPos.end());
}

@end
