# CPP09
Last project of 42 school's C++ Piscine

## How to do the Ford-Johnson merge insertion sort
I have suffered a lot with this project, but I am quite satisfied with the result, so I decided to make this short tutorial on how to implement the merge insertion sort correctly.

If you are from 42 & working on this project - do not take my code, the implementation is quite shitty (i am mostly writing C in C++), but i am pretty sure with this tutorial you will be able to implement your own.

Firstly, you will need [the book](https://seriouscomputerist.atariverse.com/media/pdf/book/Art%20of%20Computer%20Programming%20-%20Volume%203%20(Sorting%20&%20Searching).pdf) - by now you should also be able to find this link in the subject. It is very important to use this book to understand the logic of the sort and not other sources or articles from the internet. They might seem similar, but they are not *exactly right* and this result in much more comparisons in the end.

### Why do the number of comparisons matter?

This is one question that gets asked very frequently during evaluations. When sorting a container of int, merge insertion sort is definitely not the fastest way to do it. This method is optimized for the least amount of comparisons, not time complexity. But why would any sort be optimized this way?

The point of optimization is always to save resources. Let's say we are not sorting a container of int, but some arbitrary data type `T`, from which any two elements are very expensive to compare. For example, such `T` can be a one-gigabyte string (`strcmp` iterating through 1,073,741,824 characters, anyone?), or a huge object/struct loaded with all kinds of data. If comparisons are expensive and eating up resources (like time), you want to make as few of them as possible. It is indeed does not make much sense to choose merge insertion sort when `T` is a simple int, but the point of the exercise is not creating a practical use case, but understanding the algorithm.

Another thing that follows from this is that when we say we try to reduce the amount of comparisons in our code, this only means comparisons between any two `T`. Comparing the indexes of two elements is fine. Comparing the position of two iterators is fine. Comparing anything but `T` is fine, but we want to resort to comparing as few `T` with each other as possible.

### The main idea: merge insertion in 3 steps

Some people have told me there are periods when the link for the book is not accessible from the subject. Therefore I have uploaded an excerpt of the parts that we need to this repo (you can find it in the `book` folder). But if you can access the book and you have some time, it is in general a very interesting read.

If you have no time, just search for `merge insertion` (you will find the one you need on page 184). On page 185, you will find the main description of the algorithm in 3 steps:

<br>

![steps](/resources/imgs/steps.png)

<br>

What does this mean?

Let's say we have a container of 9 numbers:<br>
`2, 3, 8, 11, 3, 1, 99, 8, 0`

**Step 1** is simple: take all of the numbers you have to sort, assign them into pairs (2 neighbors are one pair), and for each pair, decide which one is the bigger number (if they are equal, then it doesn't matter).

This means we now have the pairs:<br>
`(2,3) (8,11) (3,1) (99, 8) (0)`

**Step 2** says: from all of these pairs, you need to sort the bigger elements - therefore you need to separate the big and small members of the pairs first. How you approach this depends on your individual implementation. Some people assign them to `std::pair`s. You can also have another container and put all the "small" elements there.

We have the big elements:<br>
`3, 11, 3, 99`<br>
And the small ones:<br>
`2, 8, 1, 8, 0`

Now comes the tricky part. The book says: the way you will have to sort the larger elements is *by merge insertion*. Therefore, whatever implementation you make, will have to be *recursive*. Since _merge insertion itself is step 1-3_, we will take the larger elements now, and apply the merge insertion sort to them.

Let's grab the big numbers and go back to **step 1**.<br>
Make pairs:<br>
`(3, 11), (3, 99)`<br>
Separate.<br>
`Big: 11, 99`<br>
`Small: 3, 3`

Then go back to **step 1** again (and again if needed).

When will the recursion stop? When you only have 1 pair left (in the above example `(11, 99)`, you separate that and you end up with only 1 element in your "bigger" container. That 1 element is inherently sorted. Since the "larger numbers", at least for this depth of the recursion, are sorted, you can now proceed to **step 3**.

When you arrive at **step 3** (on any depth), you have 2 containers: one contains the bigger members of the pairs, and is sorted, the other contains the smaller members of the pairs, and is unsorted.

You have to, then, insert the latter into the former, with *binary insertion*. Look at the last line on the picture, and check the indexes of the elements to insert (labeled `b`).<br> 
You can see a pattern like *3->2->5->4->11->10->9->8->7->6->21->20...*

This means: you choose the element with the 3rd index from the sorted container, *select its pair* from the unsorted one, and insert it into the former. Then do this with the element with the 2nd index, the 5th, and so on. You can see that you always jump up to a "boundary" number (5, 11, 21, etc), then count backwards until you reach what you have already covered.

These "boundary" numbers follow a pattern, which is called **Jacobstahl sequence**. Looking at fig. 13 in the book, you can see that any element of this sequence can be calculated with the formula 

<div align="center">

(2<sup>k+1</sup> + ( -1 )<sup>k </sup>) / 3

</div>

where *k* is the index of the element. So the first element will be (2<sup>1+1</sup> + ( -1 )<sup>1 </sup>) / 3 = 3 / 3 = 1. The fifth element is (2<sup>5+1</sup> + ( -1 )<sup>5 </sup>) / 3 = 63 / 3 = 21 etc.

### What is the purpose of the Jacobstahl sequence?

Why do we need to follow the Jacobstahl sequence at the insertion phase? During evaluation, the standard answer is "because this simply seems to be the most optimized order of insertion". But really: why does it work?

This is another thing that the book does not explain very clearly, but it's quite fascinating once you see the purpose, and is actually probably the most important part of the algorithm.

We are using *binary insertion* to insert the unsorted elements into the sorted container. Binary insertion is basically just the technique to apply *binary search* to find the position at which to insert. I will not explain it in detail here, because this process is very easy to find on the internet (basically you cut whatever you are searching in in half, identify which half to look in further, then cut that in half etc. Naturally this only works on a container whose elements are already sorted).

Binary insertion, on the worse case scenario, takes

<div align="center">
<img src="/resources/imgs/insertion_num.png" width="125">
</div>

comparisons to insert an element into a container of *n* elements at the right position. This expression means: *to what power would I have to raise 2 to get n (rounded down), plus one.* This happens because during binary search, you keep dividing the range of elements you parse by 2 (each division happens after one comparison), and worst case scenario, if this continues until you end up with a range of exactly one element, you need to compare your element against that one.

To use this expression in practice, for example, if you have a container of 12 elements: you need the last power of 2 that fits into 12. It is 2<sup>3</sup> (8), because 2<sup>4</sup> (16) already exceeds it, and you will need to round down, not up. Then you add 1 to it, so for a container of 12 elements, you need 4 comparisons to insert something, worst case. In below table you can see the worst-case comparisons calculated for some number of elements.

<br>

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

<br>

You can see that the comparisons always grow upon reaching the next power of 2 (2, 4, 16, etc).

Now imagine then that you need to insert a container of 11 (unsorted) elements into another container of 11 (sorted). We will examine three appraches for insertion: inserting left to right, inserting right to left, and then inserting following the Jacobstahl sequence.

*NOTE: If you have _Ligretto_ or any other colored & numbered cards, I recommend using them to try and visualize each approach for yourself (one distinct color for each container). In case you do not have any at hand, I will attach some pictures at the end of this file at the _Pictures_ section.*

**First approach - inserting left to right**

Let's start the indexing from 1 instead of 0 for convenience's sake.

You go to the 1st element (index 1) of the sorted container - let's name it A<sub>1</sub>, and *select its pair* from the unsorted one - name that B<sub>1</sub>. Because you know that B<sub>1</sub> is smaller than its pair, and you also know that A<sub>1</sub> is the smallest in the unsorted container, you need 0 comparisons to insert B<sub>1</sub>. Now you move on to A<sub>2</sub> (which now has been promoted to index 3) and insert its pair (B<sub>2</sub>). Again, you only need to compare B<sub>2</sub> with the elements *left from* A<sub>2</sub>, because you know that its smaller than A<sub>2</sub>, and everything right from A<sub>2</sub> is bigger than A<sub>2</sub>. But because you always insert left-side from your current index, each insertion will, with 100% certainty, increase the number of elements you need to perform the search on in the next turn. When you arrive to the last B to insert, you will need to do binary insertion on a container of 20 elements (from the total of 22, excluding the pair of B<sub>11</sub> and B<sub>11</sub> itself).

<br>

<div align="center">

| Index of A in original <br> container (before insertion) | Number of elements you have <br> to perform the search on | Worst-case comparisons to <br> insert B into the search field <br> (see table 1) |
|:----------:|:----------:|:----------:|
| 1 | 0 | 0 |
| 2 | 2 | 2 |
| 3 | 4 | 3 |
| 4 | 6 | 3 |
| 5 | 8 | 4 |
| 6 | 10 | 4 |
| 7 | 12 | 4 |
| 8 | 14 | 4 |
| 9 | 16 | 5 |
| 10 | 18 | 5 |
| 11 | 20 | 5 |

Total number of comparisons: **39**

</div>

<br>

**Second approach - inserting right to left**

Another approach would be to insert right to left. If you immediately seek out the A with the index 11, you will still need to compare its B with everything left from it, but this will now only mean 10 elements, not 20. You might even get lucky and get to insert it *rightmost* from the A<sub>10</sub>, which means B<sub>10</sub> will have a "search field" of only 9 elements (everything still left from A<sub>10</sub>). But when we count the number of comparisons, *we always account for the worst case*. Let's imagine everything in container B is smaller than the smallest A. This means that, as you insert right to left, in each turn you can subtract one more A from the search field, but there will be a B added instead. So your search field will have a constant size of 10 elements.

<br>

<div align="center">

| Index of A in original <br> container (before insertion) | Number of elements you have <br> to perform the search on <br> (worst case) | Worst-case comparisons to <br> insert B into the search field <br> (see table 1) |
|:----------:|:----------:|:----------:|
| 11 | 10 | 4 |
| 10 | 10 | 4 |
| 9 | 10 | 4 |
| 8 | 10 | 4 |
| 7 | 10 | 4 |
| 6 | 10 | 4 |
| 5 | 10 | 4 |
| 4 | 10 | 4 |
| 3 | 10 | 4 |
| 2 | 10 | 4 |
| 1 | 10 | 4 |

Total number of comparisons: **44**

</div>

<br>

One can of course argue that we don't have a lot of chance to get *this unlucky*. While approach 1 will *always* give you the same amount of comparisons, approach 2 at least has the chance to improve (because of the chance of inserting right from your search field). Nevertheless, it's important to reiterate that when we look at how effective a method is, we always have to look at the worst possible case.

**Now, finally: let's try the Jacobstahl sequence**.

Let's assume we have the same "unlucky" containers we had for **approach 2**: all of the elements in container B are smaller than the smallest A. Therefore, all Bs get inserted leftmost from all of the As.

We start with A<sub>1</sub> (the A with the index of 1): its pair will gets inserted leftmost from it, without any comparisons, like in **approach 1**. Then we jump to A<sub>3</sub> - our search field now consists of 3 elements: A<sub>1</sub>, A<sub>2</sub> and the already inserted B<sub>1</sub>. Then, moving backwards to A<sub>2</sub> the field remains the same size: A<sub>2</sub> itself is not part of the search field anymore, but B<sub>3</sub> has been added.

After you jump up to a "boundary index" and it sets the size of your search field, you can observe that while you move backwards, this size will remain constant (exactly like in **approach 2**). You can look at the table of how the field grows:

<br>

<div align="center">

| Index of A in original <br> container (before insertion) | Number of elements you have <br> to perform the search on <br> (worst case) | Worst-case comparisons to <br> insert B into the search field <br> (see table 1) |
|:----------:|:----------:|:----------:|
| 1 | 0 | 0 |
| 3 | 3 | 2 |
| 2 | 3 | 2 |
| 5 | 7 | 3 |
| 4 | 7 | 3 |
| 11 | 15 | 4 |
| 10 | 15 | 4 |
| 9 | 15 | 4 |
| 8 | 15 | 4 |
| 7 | 15 | 4 |
| 6 | 15 | 4 |

Total number of comparisons: **34**

</div>

<br>

If you observe the above table, you can see what the Jacobstahl sequence does beautifully. Table 1 shows that the amount of comparisons needed always increases at a field size of the next power of 2 (for example, there is an increase in comparisons at 1, 4, 8, and 16 elements). Jacobstahl *keeps your search field size just below this treshold, for as long as possible*. Since beginning from 2<sup>n</sup> elements you would have a required comparison number increase, you can be sure as hell your n<sup>th</sup> search field size will be *exactly* 2<sup>n</sup> - 1. **This** is why Jacobstahl is crazy optimized for binary insertion.

### But how to keep track of my pairs?

In my above examples, you could see perhaps the biggest challenge one can face when implementing the algorithm. Remember that in **step 1**, we had to create pairs. When it comes to **step 3**, the insertion phase, you need to strongly rely on these pairs, because when it comes to the binary insertion, each B gets inserted *left from* its pair, and everything right from its pair can be ignored. If we don't keep track of the pairs, each B needs to be inserted *on a search field covering the whole container A*. This means more comparisons than any of the approaches listed before.

But there are multiple levels of recursion between most step 1s and corresponding step 3s. Let's say you have a container of 22 elements, separating it into 11 As and 11 Bs is the very first step in your algorithm. Merging the 11 Bs into the now-sorted As should be the very last. It's easy to say "pick an A and find its pair" - but how to know which B used to belong to it?

The first and most important thing I want to say about this: **DO NOT use std::find for this purpose!**

This approach includes not taking duplicates, then for every A, saving what your original B was at **step 1**, and using `std::find` to find it in the unsorted container when you arrive at **step 3** (this could return in a false positive if you take duplicates, hence the exclusion). A lot of people do this, but it's wrong, and is completely against the purpose of the algorithm.

Like I mentioned earlier, the point of merge insertion is sorting your elements with the least amount of comparisons between any two `T`. `std::find` will use binary search to find its target in the unsorted container - on each turn comparing two `T` which each other, which could be completely avoided, had we kept proper track of the relationship between As and Bs from the beginning. Remember that our base assumption is that comparing any two `T` is a very expensive operation.

Since `std::find` is basically just a binary search, using it for the binary insertion phase (finding where exactly to insert within your custom boundaries) is, of course, fine. While I would personally recommend you to write your own binary search algorithm to better understand the process, this is also a valid approach. **But using std::find to find which B belongs to a certain A is not acceptable.** A properly implemented Ford-Johnson should have no issue with duplicates.

There are many other ways to tackle this challenge, although this is arguably the hardest part of any implementation. [Xaver](https://github.com/rwxg) had a solution using `std::pair`s and "ancestor pointers" pointing at the pairs they were derived from. I also know [Michi](https://github.com/HeiMichael) treats groups of `T` that have ever been compared as one unit that moves together, and then always compares the "top" element of two units with each other (see picture).

<div align="center">
<img src="/resources/imgs/groups.jpg" width="600">

  Grouping approach. After 3rd comparison we have arrived at **step 3** for the first time.
</div>
