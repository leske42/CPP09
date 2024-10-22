# CPP09
Last project of 42 school's C++ Piscine

## How to do the Ford-Johnson merge insertion sort
I have suffered a lot with this project, but I am quite satisfied with the result, so I decided to make this short tutorial on how to implement the merge insertion sort correctly.

If you are from 42 & working on this project - do not take my code, the implementation is quite shitty (i am mostly writing C in C++), but i am pretty sure with this tutorial you will be able to implement your own.

Firstly, you will need [the book](https://seriouscomputerist.atariverse.com/media/pdf/book/Art%20of%20Computer%20Programming%20-%20Volume%203%20(Sorting%20&%20Searching).pdf) - by now you should also be able to find this link in the subject. It is very important to use this book to understand the logic of the sort and not other sources or articles from the internet. They might seem similar, but they are not *exactly right* and this result in much more comparisons in the end.

### Why do the number of comparisons matter?

This is one question that gets asked very frequently during evaluations. When sorting a container of int, merge insertion sort is definitely not the fastest way to do it. This method is optimized for the least amount of comparisons, not time complexity. Why would any sort be optimized this way?

The point of optimization is always to save resources. Let's say we are not sorting a container of int, but some arbitrary data type `T`, from which any two elements are very expensive to compare. For example, such `T` can be a one-gigabyte string (`strcmp` iterating through 1,073,741,824 characters, anyone?), or a huge object/struct loaded with all kinds of data. If comparisons are expensive and eating up resources (like time), you want to make as few of them as possible. It is indeed does not make much sense to choose merge insertion sort when `T` is a simple int, but the point of the exercise is not creating a practical use case, but understanding the algorithm.

Another thing that follows from this is that when we say we try to reduce the amount of comparisons in our code, this only means comparisons between any two `T`. Comparing the indexes of two elements is fine. Comparing the position of two iterators is fine. Comparing anything but `T` is fine, but we want to resort to comparing as few `T` with each other as possible.

### The main idea: merge insertion in 3 steps

Some people have told me there are periods when the link for the book is not accessible from the subject. Therefore I have uploaded an excerpt of the parts that we need to this repo (you can find it in the `book` folder). But if you can access the book and you have some time, it is in general a very interesting read.

If you have no time, just search for `merge insertion` (you will find the one you need on page 184). On page 185, you will find the main description of the algorithm in 3 steps:

![image](https://github.com/user-attachments/assets/3ce052b7-4fd0-4880-aa0c-02713b6a0c61)

What does this mean?

Let's say we have a container of 9 numbers:<br>
`2, 3, 8, 11, 3, 1, 99, 8, 0`

**Point 1** is simple: take all of the numbers you have to sort, assign them into pairs (2 neighbors are one pair), and for each pair, decide which one is the bigger number (if they are equal, then it doesn't matter).

This means we now have the pairs:<br>
`(2,3) (8,11) (3,1) (99, 8) (0)`

**Point 2** says: from all of these pairs, you need to sort the bigger elements - therefore you need to separate the big and small members of the pairs first. You can, for example, have another container and put all the "small" elements there.

We have the big elements:<br>
`3, 11, 3, 99`<br>
And the small ones:<br>
`2, 8, 1, 8, 0`

Now comes the tricky part. The book says: the way you will have to sort the larger elements is *by merge insertion*. Therefore, whatever implementation you make, will have to be *recursive*. Since merge insertion itself is point 1-3, we will take the larger elements now, and apply the merge insertion sort to them.

Let's grab the big numbers and go back to **point 1**.<br>
Make pairs:<br>
`(3, 11), (3, 99)`<br>
Separate.<br>
`Big: 11, 99`<br>
`Small: 3, 3`

Then go back to **point 1** again (and again if needed).

When will the recursion stop? When you only have 1 pair left (in the above example `(11, 99)`, you separate that and you end up with only 1 element in your "bigger" container. That 1 element is inherently sorted. Since the "larger numbers", at least for this depth of the recursion, are sorted, you can now proceed to **point 3**.

When you arrive at **point 3** (on any depth), you have 2 containers: one contains the bigger members of the pairs, and is sorted, the other contains the smaller members of the pairs, and is unsorted.

You have to, then, insert the latter into the former, with *binary insertion*. Look at the last line on the picture, and check the indexes of the elements to insert (labeled `b`).<br> 
You can see a pattern like *3->2->5->4->11->10->9->8->7->6->21->20...*

This means: you choose the element with the 3rd index from the sorted container, *select its pair* from the unsorted one, and insert it into the former. Then do this with the element with the 2nd index, the 5th, and so on. You can see that you always jump up to a "boundary" number (5, 11, 15, etc), then count backwards until you reach what you have already covered.

These "boundary" numbers follow a pattern, which is called **Jacobstahl sequence**. Looking at fig. 13 in the book, you can see that any element of this sequence can be calculated with the formula 

$$ (2^{k+1} + (-1)^k)/3 $$

where *k* is the index of the element. So the first element will be $(2^{1 + 1} + (-1)^1)/3 = 3/3 = 1$. The fifth element is $(2^{5 + 1} + (-1)^5)/3 = 63/3 = 21$ etc.

### What is the purpose of the Jacobstahl sequence?

Why do we need to follow the Jacobstahl sequence at the insertion phase? During evaluation, the standard answer is "because this simply seems to be the most optimized order of insertion". But really: why does it work?

This is another thing that the book does not explain very clearly, but it's quite fascinating once you see the purpose, and is actually probably the most important part of the algorithm.

We are using *binary insertion* to insert the unsorted elements into the sorted container. Binary insertion is basically just the technique to apply *binary search* to find the position at which to insert. I will not explain it in detail here, because this process is very easy to find on the internet (basically you cut whatever you are searching in in half, identify which half to look in further, then cut that in half etc. Naturally this only works on a container whose elements are already sorted).

Binary insertion, on the worse case scenario, takes $\lfloor log_2(n)\rfloor + 1$ comparisons to insert an element into a container of *n* elements at the right position. This expression means: *to what power would I have to raise 2 to get n (rounded down), plus one.* This happens because during binary search, you keep dividing the range of elements you parse by 2 (each division happens after one comparison), and worst case scenario, if this continues until you end up with a range of exactly one element, you need to compare your element against that one.

To use this expression in practice, for example, if you have a container of 12 elements: you need the last power of 2 that fits into 12. It is $2^3$ (8), because $2^4$ (16) already exceeds it, and you will need to round down, not up. Then you add 1 to it, so for a container of 12 elements, you need 4 comparisons to insert something, worst case. In below table you can see the worst-case comparisons calculated for some number of elements.

<div align="center">

| Number of elements | Worst-case comparisons needed |
|:----------:|:----------:|
| 1 | 1 |
| 2 | 2 |
| 3 | 2 |
| 4 | 3 |
| 5 | 3 |
| 6 | 3 |
| 7 | 3 |
| 8 | 4 |
| 9 | 4 |
| ... | 4 |
| 16 | 5 |
| 17 | 5 |

</div>


