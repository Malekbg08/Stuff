/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Malek Ben Ghachem (malek.ben-ghachem@univ-tlse3.fr)

 Implantation du TAD Queue étudié en cours.

 */
/*-----------------------------------------------------------------*/
#include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void bstree_remove_node(ptrBinarySearchTree *t, ptrBinarySearchTree current);

/*------------------------  BSTreeType  -----------------------------*/

struct _bstree {
    BinarySearchTree *parent;
    BinarySearchTree *left;
    BinarySearchTree *right;
    int root;
};

/*------------------------  BaseBSTree  -----------------------------*/

BinarySearchTree *bstree_create(void) {
    return NULL;
}

/* This constructor is private so that we can maintain the oredring invariant on
 * nodes. The only way to add nodes to the tree is with the bstree_add function
 * that ensures the invariant.
 */
BinarySearchTree *bstree_cons(BinarySearchTree *left, BinarySearchTree *right, int root) {
    BinarySearchTree *t = malloc(sizeof(struct _bstree));
    t->parent = NULL;
    t->left = left;
    t->right = right;
    if (t->left != NULL)
        t->left->parent = t;
    if (t->right != NULL)
        t->right->parent = t;
    t->root = root;
    return t;
}

void bstree_delete(ptrBinarySearchTree *t) {
  if(bstree_empty(*t))
    return;
  bstree_delete(&(*t)->left);
  bstree_delete(&(*t)->right);
  free((*t));
}

bool bstree_empty(const BinarySearchTree *t) {
    return t == NULL;
}

int bstree_root(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->root;
}

BinarySearchTree *bstree_left(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->left;
}

BinarySearchTree *bstree_right(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->right;
}

BinarySearchTree *bstree_parent(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->parent;
}

/*------------------------  BSTreeDictionary  -----------------------------*/

/* Obligation de passer l'arbre par référence pour pouvoir le modifier */
void bstree_add(ptrBinarySearchTree *t, int v) {
    ptrBinarySearchTree *current=t;
    BinarySearchTree* parent=NULL;
    while(*current!=NULL){
      parent=*current;
      if((*current)->root == v)
        return;
      if((*current)->root>v){
        current=&((*current)->left);
      } else
        current=&((*current)->right);
    }
    *current=bstree_cons(NULL,NULL,v);
    (*current)->parent=parent;

}

bool bstree_search(const BinarySearchTree *t, int v) {
  while(!bstree_empty(t)){
    if(v<bstree_root(t)) t = bstree_left(t);
    else if (v>bstree_root(t)) t = bstree_right(t);
    else break;
  }
  return !bstree_empty(t);
}

BinarySearchTree *bstree_successor(const BinarySearchTree *x) {
    BinarySearchTree *alt = x->right;
    if(alt !=NULL){
      while(alt->left!=NULL){
        alt=alt->left;
      }
    }
    else{
      alt=x->parent;
      while(alt!=NULL && (x==alt->right)){
        x=alt;
        alt=alt->parent;
      }
    }
    return alt;
}

BinarySearchTree *bstree_predecessor(const BinarySearchTree *x) {
  BinarySearchTree *alt = x->left;
  if(alt !=NULL){
    while(alt->right!=NULL){
      alt=alt->right;
    }
  }
  else{
    alt=x->parent;
    while(alt!=NULL && (x==alt->left)){
      x=alt;
      alt=alt->parent;
    }
  }
  return alt;
}
////////////////////////////////////////////////               ////////////////////////////////////////////////
//                                     A AMELIORER !!!!!!!!!!!!!!!!!!!
////////////////////////////////////////////////               ////////////////////////////////////////////////                                                 //
void bstree_swap_nodes(ptrBinarySearchTree *tree, ptrBinarySearchTree from, ptrBinarySearchTree to) {
    assert(!bstree_empty(*tree) && !bstree_empty(from) && !bstree_empty(to));

    (void)tree;
    int valfrom=(from)->root;
    int valto=(to)->root;
    (from)->root=valto;
    (to)->root=valfrom;
    /*
    (void)tree;
      BinarySearchTree* ech=from;
      BinarySearchTree* ech2=from->right;
      BinarySearchTree* ech3=from->left;
      BinarySearchTree* ech4=to;

      if(from->left!=NULL){
        from->left->parent=to;
      }

      if(from->right!=NULL){
        from->right->parent=to;

      }
      if(to->left!=NULL){
        to->left->parent=from;
      }

      if(to->right!=NULL){
        to->right->parent=from;
      }

      from->right=to->right;
      from->left=to->left;
      to->left=ech3;
      to->right=ech2;
    if(from->parent->right == from){
        from->parent->right=to;
        from->parent=ech4->parent;

    }
    else if(from->parent->left == from){
      from->parent->left=to;
      from->parent=ech4->parent;

    }

    if(to->parent->right == to){
      to->parent->right=ech;
      to->parent=ech->parent;
    }
    else if(to->parent->left == to){
      to->parent->left=ech;
      to->parent=ech->parent;

    }
*/
}
////////////////////////////////////////////////               ////////////////////////////////////////////////
////////////////////////////////////////////////               ////////////////////////////////////////////////


// t -> the tree to remove from, current -> the node to remove
void bstree_remove_node(ptrBinarySearchTree *t, ptrBinarySearchTree current) {
    assert(!bstree_empty(*t) && !bstree_empty(current));
    /////////////////   CAS 2 FILS /////////////////////////
    if((current)->left!=NULL && (current)->right!=NULL){
      BinarySearchTree* succ = bstree_successor(current);
        if(succ!=NULL){
          bstree_swap_nodes(t,current,succ);
          bstree_remove_node(t,succ); //appel rec

        }

    }
    /////////////////   CAS 1 FILS /////////////////////////
    else if((current->left!=NULL) ^ (current->right!=NULL)){
      if((current)->left!=NULL ){
        BinarySearchTree *fils=(current)->left;
        if(bstree_parent(current)->left){
          fils->parent=bstree_parent(current);
          bstree_parent(current)->left=fils;
        }
        else{
          fils->parent=bstree_parent(current);
          bstree_parent(current)->right=fils;
        }
      }
      else if((current)->right!=NULL){
        BinarySearchTree *fils=(current)->right;
        if(bstree_parent(current)->left){
          fils->parent=bstree_parent(current);
          bstree_parent(current)->left=fils;
        }
        /////////////////   CAS 0 FILS /////////////////////////

        else{
          fils->parent=bstree_parent(current);
          bstree_parent(current)->right=fils;
        }
      }
      free(current);

    }

    else {
        if(bstree_parent(current)->left==current){
          bstree_parent(current)->left=NULL;
        }
        else if(bstree_parent(current)->right==current){
          bstree_parent(current)->right=NULL;
        }
        free(current);

    }
}


//Pour cette fonction si le nœud a supprimer possede deux fils,
//il sera echange dans l’arbre avec son successeur avant d’etre supprimé.

void bstree_remove(ptrBinarySearchTree *t, int v) {
  BinarySearchTree* elem=*t;
  bool trouve=false;
  while(!bstree_empty(elem)){
    if(v<bstree_root(elem)) elem = bstree_left(elem);
    else if (v>bstree_root(elem)) elem = bstree_right(elem);
    else{
      trouve=true;
      break;
    }
  }
  if(trouve)
  bstree_remove_node(t,elem);
}

/*------------------------  BSTreeVisitors  -----------------------------*/

void bstree_depth_prefix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
  if(bstree_empty(t))
    return;
  f(t,userData);
  bstree_depth_prefix(t->left,f,userData);
  bstree_depth_prefix(t->right,f,userData);
}

void bstree_depth_infix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
  if(bstree_empty(t))
    return;
  bstree_depth_infix(t->left,f,userData);
  f(t,userData);
  bstree_depth_infix(t->right,f,userData);
}

void bstree_depth_postfix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
  const BinarySearchTree *current =t;
  const BinarySearchTree *prev=bstree_parent(t);
  const BinarySearchTree *next=bstree_parent(t);
  while(!bstree_empty(current)){
    if(prev == bstree_parent(current)){
      prev=current;
      next=bstree_left(current);
    }
    if(bstree_empty(next) || prev==bstree_left(current)){
      prev=current;
      next=bstree_right(current);
    }
    if(bstree_empty(next) || prev==bstree_right(current)){
      prev=current;
      next=bstree_parent(current);
      f(current,userData);

    }
    current=next;
  }

}

void bstree_iterative_depth_infix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
  const BinarySearchTree *current =t;
  const BinarySearchTree *prev=bstree_parent(t);
  const BinarySearchTree *next=bstree_parent(t);
  while(!bstree_empty(current)){
    if(prev == bstree_parent(current)){
      prev=current;
      next=bstree_left(current);
    }
    if(bstree_empty(next) || prev==bstree_left(current)){
      f(current,userData);
      prev=current;
      next=bstree_right(current);
    }
    if(bstree_empty(next) || prev==bstree_right(current)){
      prev=current;
      next=bstree_parent(current);
    }
    current=next;
  }
}

void bstree_iterative_breadth_prefix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
  const BinarySearchTree *current =t;
  /*const BinarySearchTree *prev=bstree_parent(t);
  const BinarySearchTree *next=bstree_parent(t);
  int tabelem[100];
  int tabelemvisites[100];
  */
  Queue* queue=createQueue();
  const BinarySearchTree *elem = current;
  const BinarySearchTree *elem2=elem;
  queuePush(queue,elem);
  while(queueSize(queue)>0){
    const BinarySearchTree* currentvaleur=queueTop(queue);
    if(bstree_left(currentvaleur)!=NULL){
      elem2 = currentvaleur->left;
      queuePush(queue,elem2);
    }
    if(bstree_right(currentvaleur)!=NULL){
      elem2 = currentvaleur->right;
      queuePush(queue,elem2);
    }
    f(currentvaleur,userData);

    queue=queuePop(queue);
  }
/*
  while(!bstree_empty(current)){
    if(prev == bstree_parent(current)){
      f(current,userData);
      prev=current;
      next=bstree_left(prev);
    }
    if(bstree_empty(next) || prev==bstree_left(current)){
      prev=current;
      next=bstree_right(current);
    }
    if(bstree_empty(next) || prev==bstree_right(current)){
      prev=current;
      next=bstree_parent(current);
    }
    *elem = &current->root;
    queuePush(queue,elem);
    current=next;
  }
  while(!queueEmpty(queue)){
    queueTop(queue);
    queuePop(queue);
  }
  */
  deleteQueue(&queue);

}

/*------------------------  BSTreeIterator  -----------------------------*/

struct _BSTreeIterator {
    /* the collection the iterator is attached to */
    const BinarySearchTree *collection;
    /* the first element according to the iterator direction */
    const BinarySearchTree *(*begin)(const BinarySearchTree *);
    /* the current element pointed by the iterator */
    const BinarySearchTree *current;
    /* function that goes to the next element according to the iterator direction */
    BinarySearchTree *(*next)(const BinarySearchTree *);
};

/* minimum element of the collection */
const BinarySearchTree *goto_min(const BinarySearchTree *e) {
  const BinarySearchTree *tree=e;
  while(tree->left!=NULL){
      tree=tree->left;

  }
  return tree;
}

/* maximum element of the collection */
const BinarySearchTree *goto_max(const BinarySearchTree *e) {
  const BinarySearchTree *tree=e;

  while(tree->right!=NULL){
      tree=tree->right;

  }
  return tree;
}

/* constructor */
BSTreeIterator *bstree_iterator_create(const BinarySearchTree *collection, IteratorDirection direction) {
    BSTreeIterator *it = malloc(sizeof(BSTreeIterator) );
    IteratorDirection dir=forward;
    it->collection=collection;
    //printf("haha");
    if(direction==dir){
      it->begin=goto_min;
      it->next=bstree_successor;
      it->current=goto_min(collection);

    }
    else{
      it->begin=goto_max;
      it->next=bstree_predecessor;
      it->current=goto_max(collection);
    }
    return it;
  }


/* destructor */
void bstree_iterator_delete(ptrBSTreeIterator *i) {
    free(*i);
    *i = NULL;
}

BSTreeIterator *bstree_iterator_begin(BSTreeIterator *i) {
    i->current = i->begin(i->collection);
    return i;
}

bool bstree_iterator_end(const BSTreeIterator *i) {
    return i->current == NULL;
}

BSTreeIterator *bstree_iterator_next(BSTreeIterator *i) {
    i->current = i->next(i->current);
    return i;
}

const BinarySearchTree *bstree_iterator_value(const BSTreeIterator *i) {
    return i->current;
}
