/* Rafael Gomez-Jordana
 *
 * This is a short code sample developed for my application to Rapyuta Robotics. Do not expect to find exceptionally advanced code, but
 * rather some of the C++ structures that I am currently familiar with, like Class structures and inheritance, Templates or STL Vectors.
 * It also shows some of the new cool features of C++11 that I know how to implement, i.e. Shared Pointers, the new random generation library
 * automatic type deduction and the new range-based loops.
 *
 * The program dynamically allocates a number of objects of the class Shape which are randomly generated. Three vectors of shared pointers
 * store these objects: One for all the shapes, one only for the shapes of type circle, and another for shapes of type square.
 *
 * Then, the vector that contains all of the objects is cleared. Thanks to the capabilities of shared_pointers, the other two vectors keep
 * the objects alive until those are cleared too.
 *
 * 26th April 2016
 *
 * */

#include <iostream>
#include <memory>
#include <vector>
#include <random>

#define NUMBER_OF_SHAPES 100

using namespace std;

//Definition of a simple Shape class with a virtual method and two derived classes.
class Shape
{
private:
    float m_center_x;
    float m_center_y;
public:
    Shape(float center_x, float center_y) {
        m_center_x = center_x;
        m_center_y = center_y;
    }
    virtual void Draw(){
        cout<<"I don't know what to draw!"<<endl;
    }
};

class Circle : public Shape{
    //In C++11 Constructors are inherited automatically.
public:
    using Shape::Shape;
    void Draw(){
        cout<<"I will draw a circle!"<<endl;
    }
};

class Square : public Shape{
public:
    using Shape::Shape;
    void Draw(){
        cout<<"I will draw a squaaaare!"<<endl;
    }
};

//Aliasing to make syntax easier.
typedef shared_ptr<Shape> shape_ptr;


/*
 * Populates a vector of shared_ptr<Shape> aka shape_ptr with random initializations of
 * Circles and Squares
 * */
void randomlyPopulate(vector<shape_ptr>& vec){
    //New C++11 Random library
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<float> rnd_center(10.0, 12.0);
    uniform_int_distribution<int> coin(0,1);

    float rnd_x, rnd_y;
    bool is_circle;

    for(auto i=0; i<NUMBER_OF_SHAPES; i++){
        rnd_x = rnd_center(mt);
        rnd_y = rnd_center(mt);
        is_circle = coin(mt);

        if(is_circle) {
            shape_ptr aux_shape(new Circle(rnd_x,rnd_y));
            vec.push_back(aux_shape);
        }
        else {
            shape_ptr aux_shape(new Square(rnd_x,rnd_y));
            vec.push_back(aux_shape);
        }
    }

}
/*
 * Fills a second pointer vector with only objects of the desired type defined by
 * the template
 * */
template <class t_type> void selectShapes(vector<shape_ptr>& origin, vector<shape_ptr>& to_fill)
{
    t_type aux(0,0);
    for(auto& my_shape : origin){
        if(typeid(aux) == typeid(*my_shape)) to_fill.push_back(my_shape);
    }
}

int main(int argc, char *argv[])
{

    //Vectors of shared pointers are used to dynamically allocate the shapes.
    vector<shape_ptr> all_shapes;
    vector<shape_ptr> only_circles;
    vector<shape_ptr> only_squares;

    //The vectors are filled: the first one randomly and the other two with selections from the first one.
    randomlyPopulate(all_shapes);
    selectShapes<Circle>(all_shapes,only_circles);
    selectShapes<Square>(all_shapes,only_squares);

    cout<<"There are:"<<endl;
    cout<<"Number of shapes: "<<all_shapes.size()<<endl;
    cout<<"Number of circles: "<<only_circles.size()<<endl;
    cout<<"Number of squares: "<<only_squares.size()<<endl;

    //The vector containing pointers to all_shapes is deleted, but shapes themselves should not get deleted becouse the other two vectors remain.
    all_shapes.clear();


    //Did they survive? Check with new C++11 range-based for loop with automatic type deduction (would be shape_ptr in this case).
    for(auto& my_shape : only_circles)
    {
        my_shape->Draw();
    }
    //Memory is freed.
    only_circles.clear();
    only_squares.clear();

    return 0;
}

