//
//  @author raver119@gmail.com
//

#include <op_boilerplate.h>
#if NOT_EXCLUDED(OP_broadcast_dynamic_shape)

//#include <ops/declarable/headers/parity_ops.h>
#include <ops/declarable/CustomOperations.h>
#include <ops/declarable/helpers/bds.h>

namespace nd4j {
    namespace ops {
        CUSTOM_OP_IMPL(broadcast_dynamic_shape, 2, 1, false, 0, 0) {

            NDArray<T>* x_shape = INPUT_VARIABLE(0);
            NDArray<T>* y_shape = INPUT_VARIABLE(1);
            
            REQUIRE_TRUE(x_shape->isVector(), 0, "broadcast_dynamic_shape: The first argument should be a vector");
            REQUIRE_TRUE(y_shape->isVector(), 0, "broadcast_dynamic_shape: The second argument should be a vector");

            NDArray<T>* output = OUTPUT_VARIABLE(0);
     
            return helpers::bdsFunctor(x_shape, y_shape, output);
        }

        DECLARE_SHAPE_FN(broadcast_dynamic_shape) {
            auto shapeList = SHAPELIST();
            
            auto theFirst = inputShape->at(0);
            auto theSecond = inputShape->at(1);

            auto theFirstLen = shape::sizeAt(theFirst, -1);
            auto theSecondLen = shape::sizeAt(theSecond, -1);

            Nd4jLong* newshape;
    
            auto shapeLength = nd4j::math::nd4j_max(theFirstLen, theSecondLen);

            ALLOCATE(newshape, block.getWorkspace(), shape::shapeInfoLength(1), Nd4jLong);
            shape::shapeVector(shapeLength,  newshape);

            shapeList->push_back(newshape); 
            return shapeList;
        }

    }
}

#endif