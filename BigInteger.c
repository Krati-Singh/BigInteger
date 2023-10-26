#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
  int data;
  struct node *next;
};

struct BigInteger
{
  int length;
  struct node *link;
};

struct node *createNode (int data)
{
  struct node *itr = (struct node *) malloc (sizeof (struct node));
  if (itr)
    {
      itr->data = data;
      itr->next = NULL;
    }
  return itr;
}

struct BigInteger initialize (char *str)
{
  struct BigInteger value;
  value.length = 0;
  value.link = NULL;
  int len = strlen (str);
  int i = 0;
  for (i=0; i < len; i++)
    {
      if (str[i] < '0' || str[i] > '9')
	{
	  printf ("Invalid .\n");
	  exit (1);
	}
      int digit = str[i] - '0';
      struct node *itr = createNode (digit);
      if (!itr)
	{
	  printf ("Memory allocation failed.\n");
	  exit (1);
	}
      itr->next = value.link;
      value.link = itr;
      value.length++;
    }
  if (value.length == 0)
    {
      value.length = 1;
      value.link = createNode (0);
    }

  return value;
}

//add two BigIntegers
struct BigInteger add (struct BigInteger a, struct BigInteger b)
{
  struct BigInteger res;
  res.length = 0;
  res.link = NULL;

  int carry = 0, sum = 0;
  struct node *temp1 = a.link;
  struct node *temp2 = b.link;
  while (temp1 || temp2 || carry)
    {
      sum = carry;
      if (temp1)
	{
	  sum += temp1->data;
	  temp1 = temp1->next;
	}
      if (temp2)
	{
	  sum += temp2->data;
	  temp2 = temp2->next;
	}
      carry = sum / 10;
      struct node *itr = createNode (sum % 10);
      if (res.link == NULL)
	{
	  res.link = itr;
	}
      else
	{
	  struct node *current = res.link;
	  while (current->next)
	    {
	      current = current->next;
	    }
	  current->next = itr;
	}

      res.length++;
    }
  return res;
}

struct BigInteger sub (struct BigInteger a, struct BigInteger b)
{
  struct BigInteger res;
  res.length = 0;
  res.link = NULL;

  int borrow = 0, diff = 0;
  struct node *temp1 = a.link;
  struct node *temp2 = b.link;
  while (temp1 || temp2)
    {
      diff = borrow;

      if (temp1)
	{
	  diff += temp1->data;
	  temp1 = temp1->next;
	}
      if (temp2)
	{
	  diff -= temp2->data;
	  temp2 = temp2->next;
	}
      if (diff < 0)
	{
	  diff += 10;
	  borrow = -1;
	}
      else
	borrow = 0;

      struct node *itr = createNode (diff);
      if (res.link == NULL)
	{
	  res.link = itr;
	}
      else
	{
	  struct node *current = res.link;
	  while (current->next)
	    {
	      current = current->next;
	    }
	  current->next = itr;
	}

      res.length++;
    }
  struct node *current = res.link;
  struct node *last = NULL;
  while (current)
    {
      if (current->data != 0)
	{
	  last = current;
	}
      current = current->next;
    }

  if (last)
    {
      last->next = NULL;
    }
  else
    {
      res.link = createNode (0);
    }
  return res;
}

struct BigInteger mul (struct BigInteger a, struct BigInteger b)
{
  struct BigInteger res;
  res.length = 1;
  res.link = createNode (0);

  struct node *temp2 = b.link;
  int position = 0;	

  while (temp2)
    {
      int value = temp2->data;
      struct BigInteger multiply;
      multiply.length = 0;
      multiply.link = NULL;
      struct node *temp1 = a.link;
      int carry = 0;

      while (temp1)
	{
	  int total = (temp1->data * value) + carry;
	  carry = total / 10;
	  struct node *itr = createNode (total % 10);

	  if (multiply.link == NULL)
	    {
	      multiply.link = itr;
	    }
	  else
	    {
	      struct node *current = multiply.link;
	      while (current->next)
		{
		  current = current->next;
		}
	      current->next = itr;
	    }

	  temp1 = temp1->next;
	}

      if (carry > 0)
	{
	  struct node *itr = createNode (carry);
	  if (multiply.link == NULL)
	    {
	      multiply.link = itr;
	    }
	  else
	    {
	      struct node *current = multiply.link;
	      while (current->next)
		{
		  current = current->next;
		}
	      current->next = itr;
	    }
	}
      for (int i = 0; i < position; i++)
	{
	  struct node *zero = createNode (0);
	  zero->next = multiply.link;
	  multiply.link = zero;
	}

      // Add the multiply to the res
      res = add (res, multiply);

      temp2 = temp2->next;
      position++;
    }

  return res;
}

struct node* reverseList(struct node* head) {
    struct node* prev = NULL;
    struct node* current = head;
    struct node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev; 
}

struct node* copyList(struct node* head) {
    struct node* currentHead = NULL;
    struct node* current = head;
    struct node* tail = NULL;

    while (current != NULL) {
        struct node* itr = (struct node*)malloc(sizeof(struct node));
        itr->data = current->data;
        itr->next = NULL;

        if (tail == NULL) {
            currentHead = itr;
            tail = itr;
        } else {
            tail->next = itr;
            tail = itr;
        }

        current = current->next;
    }

    return currentHead;
}

int compare(struct BigInteger num1, struct BigInteger num2) 
{
    struct node* temp1 = num1.link;
    struct node* temp2 = num2.link;
    int l1 = 0;
    int l2 = 0;

    while (temp1 != NULL)
    {
        l1++;
        temp1 = temp1->next;
    }

    while (temp2 != NULL) 
    {
        l2++;
        temp2 = temp2->next;
    }

    if (l1 < l2) 
        return -1;
    else if (l1 > l2) 
        return 1;
    else 
    {
        struct node* rev1 = copyList(num1.link);
        temp1 = reverseList(rev1);;
        
        struct node* rev2 = copyList(num2.link);
        temp2 = reverseList(rev2); 
        while (temp1 != NULL) {
            if (temp1->data < temp2->data) 
            {
                free(rev1);  
                free(rev2); 
                return -1;
            } 
            else if (temp1->data > temp2->data) 
            {
                free(rev1);  
                free(rev2); 
                return 1;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        free(rev1);
        free(rev2);
        return 0; 
    }
}

// Function to divide two BigIntegers(returning quotient)
struct BigInteger div1(struct BigInteger dividend, struct BigInteger divisor) 
{
  struct BigInteger quotient;
  quotient.length = 1;
  quotient.link = createNode(0);

  struct BigInteger first;
  first.length = 1;
  first.link = createNode(1);

  struct BigInteger zero;
  zero.length = 1;
  zero.link = createNode(0);

  if (compare(divisor, zero) == 0) {
    printf("Error.\n");
    exit(1);
  }

  if (compare(dividend, zero) == 0) {
    return zero;
  }

  struct BigInteger remainder = dividend;

  while (compare(remainder, divisor) >= 0) 
  {
    remainder = sub(remainder, divisor);
    quotient = add(quotient, first);
  }

  return quotient;
}

// divide two BigIntegers (returning remainder)
struct BigInteger mod (struct BigInteger D, struct BigInteger divisor)
{
  struct BigInteger zero;
  zero.length = 1;
  zero.link = createNode (0);

  if (compare (divisor, zero) == 0)
    {
      printf ("Error: Division by zero.\n");
      exit (1);
    }

  struct BigInteger remainder = D;

  while (compare (remainder, divisor)>=0)
      remainder = sub (remainder, divisor);

  return remainder;
}

void Reverse (struct node *temp)
{
  if (temp == NULL)
    {
      return;
    }
  Reverse (temp->next);
  printf ("%d", temp->data);
}

// Function to display a BigInteger in reverse order
void display (struct BigInteger num)
{
  if (num.length == 0)
    {
      printf ("0\n");
      return;
    }

  Reverse (num.link);	
  printf ("\n");
}



