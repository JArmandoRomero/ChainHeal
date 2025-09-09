#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node
{
  char *name;
  int x, y;
  int cur_PP, max_PP;
  int adj_size;
  bool visited;
  struct node **adj_list;
};

struct params
{
  int initial_range;
  int jump_range;
  int num_jumps;
  int initial_power;
  double power_reduction;
};

struct answer
{
  int best_path_length;
  int current_path_length;
  struct node **best;
  struct node **current;
  int best_healing;
};

struct node **create_nodes_array(size_t *n)
{

  char buffer[1024];
  struct node *last = NULL; // temporary previous pointer
  *n = 0;

  // First, read all nodes and link them backward
  while (fgets(buffer, sizeof(buffer), stdin))
  {
    buffer[strcspn(buffer, "\r\n")] = '\0';

    struct node *node = malloc(sizeof(struct node));
    if (!node)
    {
      fprintf(stderr, "malloc failed\n");
      exit(1);
    }

    char temp[128];
    int count = sscanf(buffer, "%d %d %d %d %127[^\n]",
                       &node->x, &node->y, &node->cur_PP, &node->max_PP, temp);

    if (count != 5)
    {
      fprintf(stderr, "Line didn't match format: %s\n", buffer);
      free(node);
      continue;
    }

    // Allocate memory for name and copy
    node->name = malloc(strlen(temp) + 1);
    if (!node->name)
    {
      fprintf(stderr, "malloc failed\n");
      exit(1);
    }
    strcpy(node->name, temp);

    node->visited = false;
    node->adj_size = 0;

    // Temporary backward linkage
    node->adj_list = (struct node **)last;
    last = node;

    (*n)++;
  }

  // Allocate final array of node pointers
  struct node **nodes_array = malloc(*n * sizeof(struct node *));
  if (!nodes_array)
  {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }

  // Fill array in input order
  struct node *current = last;
  for (size_t i = *n; i > 0; i--)
  {
    nodes_array[i - 1] = current;
    current = (struct node *)current->adj_list;
  }

  // Reset adj_list for normal use
  for (size_t i = 0; i < *n; i++)
  {
    nodes_array[i]->adj_list = NULL;
  }

  return nodes_array;
}
bool adjacent(int jump_range, struct node *a, struct node *b)
{
  // Compute the differences in x and y coordinates
  int dx = a->x - b->x;
  int dy = a->y - b->y;

  // Return true if squared distance is within jump_range squared
  return (dx * dx + dy * dy) <= (jump_range * jump_range);
}

void setup_graph(int jump_range, size_t num_nodes, struct node **nodes)
{
  // Temporary array to keep track of the next insertion index for each node
  int *indexes = malloc(num_nodes * sizeof(int));
  if (!indexes)
  {
    fprintf(stderr, "malloc failed for indexes\n");
    exit(1);
  }

  // Step 1: Count neighbors and allocate adjacency arrays
  for (size_t i = 0; i < num_nodes; i++)
  {
    int count = 0;

    // Count how many other nodes are adjacent
    for (size_t j = 0; j < num_nodes; j++)
    {
      if (i != j && adjacent(jump_range, nodes[i], nodes[j]))
      {
        count++;
      }
    }

    nodes[i]->adj_size = count;
    nodes[i]->adj_list = malloc(count * sizeof(struct node *));
    if (!nodes[i]->adj_list)
    {
      fprintf(stderr, "malloc failed for adj_list of node %zu\n", i);
      exit(1);
    }

    indexes[i] = 0; // Initialize the insertion index
  }

  // Step 2: Fill adjacency lists
  for (size_t i = 0; i < num_nodes; i++)
  {
    for (size_t j = 0; j < num_nodes; j++)
    {
      if (i != j && adjacent(jump_range, nodes[i], nodes[j]))
      {
        // Place the neighbor in the correct position
        nodes[i]->adj_list[indexes[i]] = nodes[j];
        indexes[i]++; // Move to next insertion slot
      }
    }
  }

  free(indexes); // Cleanup temporary array
}

void print_adjacency(size_t num_nodes, struct node **nodes)
{
  for (size_t i = 0; i < num_nodes; i++)
  {
    // Print the node’s name
    printf("%s:\n", nodes[i]->name);

    // Print all adjacent nodes indented
    for (int j = 0; j < nodes[i]->adj_size; j++)
    {
      printf("  %s\n", nodes[i]->adj_list[j]->name);
    }

    printf("\n"); // extra line for readability
  }
}

void check_best(struct params *p, struct answer *a)
{
}

void print_best(struct params *p, struct answer *a)
{
}

void dfs(struct params *p, struct answer *a, int depth, struct node *n)
{
}

int main(int argc, char **argv)
{
  if (argc < 6)
  {
    fprintf(stderr, "usage: %s initial_range jump_range num_jumps initial_power power_reduction < input_file\n", argv[0]);
    return 0;
  }

  struct params p;
  struct answer a = {0};
  // Buffer for standard input

  // parse command line parameters on to the params struct
  p.initial_range = atoi(argv[1]);
  p.jump_range = atoi(argv[2]);
  p.num_jumps = atoi(argv[3]);
  p.initial_power = atoi(argv[4]);
  p.power_reduction = atof(argv[5]);

  size_t numberOfNodes = 0;

  struct node **nodes = create_nodes_array(&numberOfNodes);

  // printf("Total nodes: %zu\n", numberOfNodes);
  // for (size_t i = 0; i < numberOfNodes; i++)
  // {
  //   printf("Node %zu: x=%d y=%d curr_PP=%d max_PP=%d name=%s\n",
  //          i, nodes[i]->x, nodes[i]->y, nodes[i]->cur_PP, nodes[i]->max_PP, nodes[i]->name);
  // }

  // if (adjacent(p.jump_range, nodes[0], nodes[1]))
  // {
  //   printf("Node 0 and Node 1 are within jump range!\n");
  // }
  // else
  // {
  //   printf("Node 0 and Node 1 are NOT within jump range.\n");
  // }

  setup_graph(p.jump_range, numberOfNodes, nodes);
  print_adjacency(numberOfNodes, nodes);

  // Cleanup
  for (size_t i = 0; i < numberOfNodes; i++)
  {
    free(nodes[i]->name);
    free(nodes[i]);
  }
  free(nodes);

  return 0;
}
