#pragma once

template<class T>
class zCTree
{
public:
    zCTree<T>*	parent;
    zCTree<T>*	firstChild;
    zCTree<T>*	next;
    zCTree<T>*	prev;
    T*			data;
};