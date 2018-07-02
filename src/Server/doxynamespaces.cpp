/**
 * @brief the global project namespace all parts should be in.
 */
namespace OpenGMP
{
    /**
     * @brief from object oriented class implementations.
     */
    namespace Objects {}
    
    /**
     * @brief are acting mainly with components and sometimes with Objects and other Systems.
     */
    namespace Systems {}
    
    /**
     * @brief defining plain data, serialization methods and getter/setter.
     *   Getter/Setter are required to be able to expose attributes as class members to scripts.
     *   Serialization methods are used to define Write/Read methods by the component itself.
     */
    namespace Components {}

    /**
     * @brief objectoriented-objects with manipulating methods in an object oriented manner.
     **/
    namespace Types {}
}