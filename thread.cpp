#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <time.h>

using namespace std;
 #define NTHREADS 10

void *print_message_function( void *ptr );
int counter =0;
//srand (time(NULL));


int threadAmount = rand()%10 + 1;
//BINARY Search Tree
//--------------------------------------------//
struct node {
  int key;
  struct node *left, *right;
};

// Create a node
struct node *newNode(int item) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}

// Inorder Traversal
void inorder(struct node *root) {
  if (root != NULL) {
    // Traverse left
    inorder(root->left);

    // Traverse root
    cout << root->key << " -> ";

    // Traverse right
    inorder(root->right);
  }
}

// Insert a node
struct node *insert(struct node *node, int key) {
  // Return a new node if the tree is empty
  if (node == NULL) return newNode(key);

  // Traverse to the right place and insert the node
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
  // Return if the tree is empty
  if (root == NULL) return root;

  // Find the node to be deleted
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    // If the node is with only one child or no child
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    struct node *temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

// Driver code NODE TESTING CODE
/**int main() {
  struct node *root = NULL;
  root = insert(root, 8);
  root = insert(root, 3);
  root = insert(root, 1);
  root = insert(root, 6);
  root = insert(root, 7);
  root = insert(root, 10);
  root = insert(root, 14);
  root = insert(root, 4);

  cout << "Inorder traversal: ";
  inorder(root);

  cout << "\nAfter deleting 10\n";
  root = deleteNode(root, 10);
  cout << "Inorder traversal: ";
  inorder(root);
}**/

//-------------------------------------------//

//THREAD CREATION
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;



int main(int argc,char* argv[]){

  int usrInput = atoi(argv[1]);
  pthread_t thread_id[usrInput];
if(argc !=2){
  printf("ERROR: ./threads <number>\n");
  return 1;
}
else{

  for(int i=0; i<usrInput; i++){
    pthread_create(  &thread_id[i], NULL,  print_message_function, NULL);
  }

//waits for thread to finish
  for(int j =0; j < usrInput; j++){
    pthread_join(thread_id[j], NULL);

 }



printf("FINAL COUNTER VALUE: %d       ", counter);
//exit(0);}

//CHECKERS

}
}
    void *print_message_function( void *ptr ){

    //  printf("THREAD NUMEBR:  %d\n", pthread_self() );
      pthread_mutex_lock( &mutex1);
      counter++;
      printf("THREAD NUMEBR:  %ld\n", pthread_self()%100000,"Counter VALUE: %d", counter );
      pthread_mutex_unlock (&mutex1);

      return  0;
    }


/***
//insert a newNode

pthread_mutex_lock(&lock);

int main(int argc,char* argv[]){

  int randNum, amount;

  int childEventInfo;

  int waitReturn;

  randNum = rand() % 100 + 1;
  int iret1;
	pid_t pid;

  printf("Enter amount of threads you want to create: ");
  scanf("%d", amount);




  pid = fork();

  if(pid == 0){

    if (amount > 0){
      pthread_t randThreads;

      while(int i = 0; i<amount; i++){
        iret1 = pthread_create(&randThreads, NULL, print_message_function, (void*) randNum);

        }


      }else{

        perror("Enter a number greater than 0");
        exit(1);
      }
  }else if(pid <0){
    perror("fork");
    printf("There is no process running ");
    exit(1);
  }else {
    waitReturn = wait(&childEventInfo);
    printf("Child has been completed\n");

    exit(-1);
  }




  return 0;
}





***/
