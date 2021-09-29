//
//  Windy_Policy_Test.m
//  Windy_GridWorld_Test
//
//  Created by Xiaoyue Ding on 9/28/21.
//

#import <XCTest/XCTest.h>
#import "GridWorld.hpp"
#import "WindyEnv.hpp"
#import "WindyPolicy.hpp"

@interface Windy_Policy_Test : XCTestCase {
@private
    gridWorld* testWorld;
    windyEnv* testEnv;
    windyPolicy* testPolicy;
}

@end

@implementation Windy_Policy_Test

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
    vector_2D testGrid (7, std::vector<int> {0, 0, 0, 1, 1, 1, 2, 2, 1, 0});
    std::tuple<int, int> testStart {3, 0};
    std::tuple<int, int> testGoal {3, 7};
    
    testWorld = new gridWorld(testGrid, testStart, testGoal);
    testEnv = new windyEnv(*testWorld);
    testPolicy = new windyPolicy(*testEnv, 0.2);
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    delete testPolicy;
    testPolicy = nullptr;
    delete testEnv;
    testEnv = nullptr;
    delete testWorld;
    testWorld = nullptr;
}

- (void)testUpdateGetStateActionValCross {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    std::tuple<int, int> testPos_1 {3, 0}, testPos_2 {3, 1};
    std::tuple<int, int> testMove_1 {0, 1}, testMove_2 {1,0};
    testPolicy->updateStateActionValCross(testPos_1, testMove_1, -1, testPos_2, testMove_2, 0.5, 1);
    XCTAssertEqual(-0.5, testPolicy->getStateActionVal(testPos_1, testMove_1));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_1, testMove_2));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_2, testMove_1));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_2, testMove_2));
    
    testPolicy->updateStateActionValCross(testPos_1, testMove_1, -1, testPos_2, testMove_2, 0.5, 1);
    XCTAssertEqual(-0.75, testPolicy->getStateActionVal(testPos_1, testMove_1));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_1, testMove_2));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_2, testMove_1));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_2, testMove_2));
}

- (void)testUpdateGetStateActionValKing {
    std::tuple<int, int> testPos_3 {3, 0}, testPos_4 {3, 1};
    std::tuple<int, int> testMove_3 {1, 1}, testMove_4 {-1,1};
    testPolicy->updateStateActionValKing(testPos_3, testMove_3, -1, testPos_4, testMove_4, 0.5, 1);
    XCTAssertEqual(-0.5, testPolicy->getStateActionVal(testPos_3, testMove_3));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_3, testMove_4));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_4, testMove_3));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_4, testMove_4));
    
    testPolicy->updateStateActionValKing(testPos_3, testMove_3, -1, testPos_4, testMove_4, 0.5, 1);
    XCTAssertEqual(-0.75, testPolicy->getStateActionVal(testPos_3, testMove_3));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_3, testMove_4));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_4, testMove_3));
    XCTAssertEqual(0.0, testPolicy->getStateActionVal(testPos_4, testMove_4));
}

- (void)testGetPolicyMoveCross {
    testPolicy->updateStateActionValCross(std::make_tuple(3,1), std::make_tuple(1,0), -1, std::make_tuple(3,2), std::make_tuple(1,0), 0.5, 1);
    XCTAssertEqual(std::make_tuple(-1,0), testPolicy->getPolicyMove(std::make_tuple(3,1)));
    testPolicy->updateStateActionValCross(std::make_tuple(3,1), std::make_tuple(-1,0), -1, std::make_tuple(3,2), std::make_tuple(1,0), 0.5, 1);
    XCTAssertEqual(std::make_tuple(0,1), testPolicy->getPolicyMove(std::make_tuple(3,1)));
    testPolicy->updateStateActionValCross(std::make_tuple(3,1), std::make_tuple(0,1), -1, std::make_tuple(3,2), std::make_tuple(1,0), 0.5, 1);
    XCTAssertEqual(std::make_tuple(0,-1), testPolicy->getPolicyMove(std::make_tuple(3,1)));
    testPolicy->updateStateActionValCross(std::make_tuple(3,1), std::make_tuple(0,-1), -1, std::make_tuple(3,2), std::make_tuple(1,0), 0.5, 1);
    XCTAssertEqual(std::make_tuple(1,0), testPolicy->getPolicyMove(std::make_tuple(3,1)));
}

@end
