//
//  Windy_GridWorld_Test.m
//  Windy_GridWorld_Test
//
//  Created by Xiaoyue Ding on 9/24/21.
//

#import <XCTest/XCTest.h>
#import "GridWorld.hpp"

@interface Windy_GridWorld_Test : XCTestCase {
@private
    gridWorld* testWorld;
}

@end

@implementation Windy_GridWorld_Test

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
    vector_2D testGrid (7, std::vector<int> {0, 0, 0, 1, 1, 1, 2, 2, 1, 0});
    std::tuple<int, int> testStart {3, 0};
    std::tuple<int, int> testGoal {3, 7};
    
    testWorld = new gridWorld(testGrid, testStart, testGoal);
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    delete testWorld;
    testWorld = nullptr;
}

- (void)testGetGrid {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    const vector_2D& testGrid_1 = testWorld->getGrid();
    std::vector<int> testRow {0, 0, 0, 1, 1, 1, 2, 2, 1, 0};
    for (int i (0); i < static_cast<int>(testGrid_1.size()); ++i) {
        XCTAssertEqual(testRow, testGrid_1[i]);
    }
}

- (void)testGetStart {
    // This is an example of a performance test case.
    XCTAssertEqual(std::make_tuple(3, 0), testWorld->getStart());
}

- (void)testGetGoal {
    // This is an example of a performance test case.
    XCTAssertEqual(std::make_tuple(3, 7), testWorld->getGoal());
}

@end
