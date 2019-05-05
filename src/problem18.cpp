#include <iostream>
#include <fstream>
#include <string>
#include <list>

/*
 *
 *
 *
 *
 * By starting at the top of the triangle below and moving to adjacent numbers on the row below,
 * the maximum total from top to bottom is 23.
 *
 * 3
 * 7 4
 * 2 4 6
 * 8 5 9 3
 *
 * That is, 3 + 7 + 4 + 9 = 23.
 *
 * Find the maximum total from top to bottom of the triangle below:
 *
 * 75
 * 95 64
 * 17 47 82
 * 18 35 87 10
 * 20 04 82 47 65
 * 19 01 23 75 03 34
 * 88 02 77 73 07 63 67
 * 99 65 04 28 06 16 70 92
 * 41 41 26 56 83 40 80 70 33
 * 41 48 72 33 47 32 37 16 94 29
 * 53 71 44 65 25 43 91 52 97 51 14
 * 70 11 33 28 77 73 17 78 39 68 17 57
 * 91 71 52 38 17 14 91 43 58 50 27 29 48
 * 63 66 04 68 89 53 67 30 73 16 69 87 40 31
 * 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
 *
 * NOTE: As there are only 16384 routes, it is possible to solve this
 * problem by trying every route. However, Problem 67, is the same challenge
 * with a triangle containing one-hundred rows; it cannot be solved by brute force,
 * and requires a clever method! ;o)
 *
 * NOTE: I'm firstly solving via bruteforce
*/

struct node
{
    /*
     * Idea:
     *          PARENT
     *            |
     *           node, with presumably some fucking value
     *           /  \
     *         LEFT RIGHT
     */

    struct node *lchild;
    struct node *rchild;
    struct node *lparent;
    struct node *rparent;
    short value;
};


std::list<struct node*>::iterator parse_node(std::list<struct node*> *converted_line, std::list<struct node*> previous_line,std::string buffer, std::list<struct node*>::iterator p_it)
{
    short converted_buffer;
    converted_buffer = std::stoi(buffer);
    struct node *current_node = (node*) malloc(sizeof (struct node));

    if (!previous_line.size())
    {
        current_node->lchild = NULL;
        current_node->rchild = NULL;
        current_node->lparent = NULL;
        current_node->rparent = NULL;
    }
    else if (p_it == previous_line.begin()) // can we know from iterator that it is beginning or end?
    {
        current_node->lchild = NULL;
        current_node->rchild = NULL;
        current_node->lparent = NULL;
        current_node->rparent = *p_it;

        current_node->rparent->lchild = current_node;
    }
    else if (p_it == previous_line.end())
    {
        current_node->lchild = NULL;
        current_node->rchild = NULL;
        current_node->lparent = *p_it;
        current_node->rparent = NULL;

        current_node->lparent->rchild = current_node;
    }
    else
    {
        current_node->lchild = NULL;
        current_node->rchild = NULL;
        current_node->lparent = *p_it;
        current_node->rparent = *(++p_it);

        current_node->lparent->rchild = current_node;
        current_node->rparent->lchild = current_node;
    }

    current_node->value = converted_buffer;
    converted_line->push_back(current_node);

    std::cout << converted_buffer << std::endl;
    return p_it;
}

std::list<struct node*> process_line(std::string line, std::list<struct node*> previous_line, struct node* structure_to_be_populated)
{
    std::string buffer = "";
    std::list<struct node*> converted_line;
    struct node *current_node;
    std::list<struct node*>::iterator p_it = previous_line.begin();

    for (const char c : line)
    {
        if (c != ' ')
        {
            buffer.push_back(c);
            continue;
        }

        p_it = parse_node(&converted_line, previous_line, buffer, p_it);
        buffer = "";
    }

    parse_node(&converted_line, previous_line, buffer, p_it);
    return converted_line;
}


int main()
{
    std::ifstream infile("input/input18.txt");
    std::string line;

    std::list<struct node*> previous_line{};

    struct node* structure{};
    struct node* root;

    while (std::getline(infile, line))
    {
        // std::cerr << line << std::endl;
        previous_line = process_line(line, previous_line, structure);

        if (previous_line.size() == 1)
        {
            root = *(previous_line.begin());
        }
    }

    return 0;
}
