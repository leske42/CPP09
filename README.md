# CPP09
Last project of 42 school's C++ Piscine

## How to do the Ford-Johnson merge insertion sort
I have suffered a lot with this project, but I like to think my understanding became quite solid by the end. I decided to make this short tutorial, so people who are new to it can have some guideline on how to implement the merge insertion sort correctly.

**DISCLAIMER**: if you are from 42 & currently working on this project - do not take my code. The implementation itself is quite shitty anyway (I am mostly writing C in C++ and my coding style can be all over the place). But I am pretty sure with this tutorial you will be able to implement the algorithm on your own. You will not find parts telling you how to write your code or what containers/functions to use, but I do try to cover the theory and logic behind the exercise as much as I can (based on my current knowledge).

I recommend this tutorial also to students who are already done with the project, but either feel like they have not done the correct implementation and are not sure where it went wrong, or have done it correctly but there were some parts of the process they did not find very clear (for example, the purpose of the Jacobstahl sequence is not explained well in most resources, but it is very important for the sorting to work well, and is also super interesting). If you belong to this group, you can use my table of contents to choose the parts you are interested in.

[UPDATE] (14.12.2024) Ismayil has contributed a really cool tester, which you can find now in the `resources` folder. I have put the instructions for use under [a new section](#tester) in this document.

### Small table of contents

- [1. What you will need](#what-you-will-need)
- [2. Why do the number of comparisons matter?](#why-do-the-number-of-comparisons-matter)
- [3. The main idea: merge insertion in 3 steps](#the-main-idea-merge-insertion-in-3-steps)
- [4. What is the purpose of the Jacobstahl sequence?](#what-is-the-purpose-of-the-jacobstahl-sequence)
- [5. But how to keep track of my pairs?](#but-how-to-keep-track-of-my-pairs)
- [6. Testing if your implementation is correct](#testing-if-your-implementation-is-correct)
- [7. Pictures](#pictures)
   - [7.1. Mirroring](#mirroring-approach)
   - [7.2. Insertion methods](#insertion-methods)
- [8. Tester](#tester)

### What you will need

Firstly, if you have some colored/numbered cards around (like Uno or Ligretto), they will be super useful for visualizing the process of sorting (separating and insertion). During/after reading this tutorial, but before starting to code, I recommend playing around with them to better visualize the process (especially because recursion can be hard to imagine). They are super helpful for debugging too. In case you do not have access to any cards though, I have documented some of the concepts I'm talking about - you can find this in the [Pictures](#pictures) section.

You will definitely need _the book_ - by now you should be able to find the link to this in the subject. Some people have told me there are periods when the link for the book is not accessible, therefore I have uploaded an excerpt of the parts that we need to this repo (you can find it in the `resources` folder). I hope I will get no letters to take it down in the near future. If you can access the whole book and you have some time, it is in general a very interesting read.

It is very important to use this book to understand the logic of the sort and not other sources or articles from the internet. They might seem similar, but they are not *exactly right* and this can (usually will) result in your algorithm doing much more comparisons than necessary in the end.

### Why do the number of comparisons matter?

This is one question that gets asked very frequently during evaluations. When sorting a container of int, merge insertion might not be the fastest way to do it. This method is optimized to sort with the least amount of comparisons, and you will see that this oftentimes results in a lot of calculations to avoid even a single extra comparison between two ints - which can slow things down considerably. So why would any sort be optimized this way?

The point of optimization is always to save resources. Let's say we are not sorting a container of int, but some arbitrary data type `T`, from which any two elements are very expensive to compare. For example, such `T` can be a one-gigabyte string (`strcmp` iterating through 1,073,741,824 characters, anyone?), or a huge object/struct loaded with all kinds of data. If comparisons are expensive and eating up resources (like time), you want to make as few of them as possible. It is indeed does not make much sense to choose merge insertion sort when `T` is a simple int, but the point of the exercise is not creating a practical use case, but understanding the algorithm.

Another thing that follows from this is that when we say we try to reduce the amount of comparisons in our code, this only means comparisons between any two `T`. Comparing the indexes of two elements is fine. Comparing the position of two iterators is fine. Comparing anything but `T` is fine, but we want to resort to comparing as few `T` with each other as possible.

### The main idea: merge insertion in 3 steps

Take the book and search for "merge insertion" (you will find the one you need on page 184). On page 185, you will find the main description of the algorithm in 3 steps.

<br>
<div align="center">
<img src="/resources/imgs/steps.png" width="600">

  Merge insertion in 3 steps
</div>
<br>

What does this mean?

Let's say we have a container of 9 numbers:<br>
**2, 3, 8, 11, 3, 1, 99, 8, 0**

**Step 1** is simple: take all of the numbers you have to sort, assign them into pairs (2 neighbors are one pair), and for each pair, decide which one is the bigger number (if they are equal, you can choose the one you like).

This means we now have the pairs:<br>
**(2,3) (8,11) (3,1) (99, 8) (0)**

**Step 2** says: from all of these pairs, you need to sort *the bigger elements only* - therefore you need to separate the big and small members of the pairs first. How you approach this depends on your individual implementation. Some people assign them to `std::pair`s. You can also have another container and put all the "small" elements there, which is what I will imitate now because it looks much more readable.

So we have the big elements:<br>
**3, 11, 3, 99**<br>
And the small ones:<br>
**2, 8, 1, 8, 0**

Now comes the tricky part. The book says: the way you will have to sort the larger elements is *by merge insertion*. Therefore, whatever implementation you make, will likely be *recursive* (check my note below). Since _merge insertion itself is step 1-3_, we will take the larger elements now, and apply the merge insertion sort to them.

Let's grab only the big numbers and go back to **step 1**. Make pairs. Separate. Then go back to **step 1** again (and again, and again, if needed).

When will the recursion stop? When you only have 1 pair left (in the above example this will be **(11, 99)** ), you separate that and you end up with only 1 element in your "bigger" container. That 1 element is inherently sorted. Since the "larger numbers", at least for this depth of the recursion, are sorted, you can now proceed to **step 3**.

_NOTE: the recursion here is not so complex for it not to be possible to be transformed iterative. This was always on my mind while writing my own solution, which is, to be fully honest, while technically recursive, very close to iterative in spirit. This means recursivity is not a strict requirement for an algorithm to work, but I do feel like a recursive implementation is closer to the spirit of the original description._

When you arrive at **step 3** (on any applicable depth of the recursion), you have 2 containers: one contains the bigger members of the pairs, and is sorted, the other contains the smaller members of the pairs, and is unsorted. You have to, then, insert the latter into the former, with *binary insertion*. Look at the last line on the picture, and check the indexes of the elements to insert (labeled `b`).<br> 
You can see a pattern like *3->2->5->4->11->10->(9->8->7->6->21->20...)*

This means: you choose the element with the 3rd index from the sorted container, *select its pair* from the unsorted one, and insert it into the former. Then do this with the element with the 2nd index, the 5th, and so on. (The first - in code 0th - index is not listed here because, as you will see later, its pair can be inserted with 0 comparisons, so can technically be counted as an element of the sorted container). You can see that you always jump up to a "boundary" number (5, 11, 21, etc), then count backwards until you reach an index you have already covered.

These "boundary" numbers follow a pattern, which is called **Jacobstahl sequence**.  Looking at fig. 13 in the book, you can see that any element of this sequence can be calculated with the formula 

<div align="center">

(2<sup>k+1</sup> + ( -1 )<sup>k </sup>) / 3

</div>

where *k* is the index of the element. So the first element will be (2<sup>1+1</sup> + ( -1 )<sup>1 </sup>) / 3 = 3 / 3 = 1. The fifth element is (2<sup>5+1</sup> + ( -1 )<sup>5 </sup>) / 3 = 63 / 3 = 21 etc.

If you already know a Jacobstahl number *J* with the index of *k* (for example, you know that index 3 is 5), the next Jacobstahl number *J<sub>k+1</sub>* can also be calculated with a simpler formula: 

<div align="center">
<picture>
   <source media="(prefers-color-scheme: dark)" srcset="/resources/imgs/next_jacob.png" width="175">
   <source media="(prefers-color-scheme: light)" srcset="/resources/imgs/next_jacob_white.png" width="175">
   <img alt="Fallback image" src="/resources/imgs/next_jacob_white.png">
</picture>
</div>

**Is this even Jacobstahl or are we all scammed?**

Some of you who have done some research might have noticed that on the [Wikipedia page](https://en.wikipedia.org/wiki/Jacobsthal_number) (and other internet resources) about the Jacobstahl sequence, the formulas are somewhat different from what you can find in the book and in this explanation. Actually, the sequence discussed in the book is never once "officially" named as the Jacobstahl sequence, but they are certainly very similar.

On page 185, below fig. 12, the book says: "since t<sub>1</sub> = 1, we may set t<sub>0</sub> = 1 for convenience". This means that the sequence discussed starts as **1, 1, 3, 5, 11, 21, 43, 85**. The one discussed on Wikipedia has the 0th and 1st elements defined as 0 and 1, respectively, and starts as **0, 1, 1, 3, 5, 11, 21, 43**. The only difference compared to the book version is an extra zero at the beginning - therefore any element with the index *k* of the book sequence will be corresponding to the index *k + 1* of the other sequence. This leads to the difference in formulas between the two versions (in my both equations provided, I use 2<sup>k+1</sup> instead of 2<sup>k</sup>).

### What is the purpose of the Jacobstahl sequence?

Why do we need to follow the Jacobstahl sequence at the insertion phase? During evaluation, the standard answer is "because this simply seems to be the most optimized order of insertion". But really: why does it work?

This is another thing that the book does not explain very clearly, but it's quite fascinating once you see the purpose, and is actually probably the most important part of the algorithm.

We are using *binary insertion* to insert the unsorted elements into the sorted container. Binary insertion is basically just the technique to apply *binary search* to find the position at which to insert. I will not explain it in detail here, because this process is very easy to find on the internet (basically you cut whatever you are searching in in half, identify which half to look in further, then cut that in half etc. Naturally this only works on a container whose elements are already sorted).

Binary insertion, on the worse case scenario, takes

<div align="center">
<picture>
   <source media="(min-width: 769px) and (prefers-color-scheme: dark)" srcset="/resources/imgs/insertion_num.png" width="125">
   <source media="(max-width: 768px) and (prefers-color-scheme: dark)" srcset="/resources/imgs/tiny.jpg">
   <source media="(min-width: 769px) and (prefers-color-scheme: light)" srcset="/resources/imgs/insertion_num_white.png" width="125">
   <source media="(max-width: 768px) and (prefers-color-scheme: light)" srcset="/resources/imgs/tiny.jpg">
   <img alt="Fallback image" src="/resources/imgs/insertion_num.png">
</picture>
</div>

comparisons to insert an element into a container of *n* elements at the right position. This expression means: *to what power would I have to raise 2 to get n (rounded down), plus one.* This happens because during binary search, you keep dividing the range of elements you parse by 2 (each division happens after one comparison), and if this continues until you end up with a range of exactly one element, you need to compare your element against that one.

To use this expression in practice, for example, if you have a container of 12 elements: you need the last power of 2 that fits into 12. It is 2<sup>3</sup> (8), because 2<sup>4</sup> (16) already exceeds it, and you will need to round down. Then you add 1 to it, so for a container of 12 elements, you need 4 comparisons to insert something, worst case. In below table you can see the worst-case comparisons calculated for some number of elements.

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

You can see that the comparisons always grow upon reaching the next power of 2 (2, 4, 8, 16, etc).

Now imagine then that you need to insert a container of 11 (unsorted) elements into another container of 11 (sorted). We will examine three appraches for insertion: inserting left to right, inserting right to left, and then inserting following the Jacobstahl sequence.

*NOTE 1: Since (our version of) Jacobstahl begins with 1, we will need to start the indexing from 1 instead of the usual 0. We can also iterate the Jacobstahl beginning from the 1st element, because index 0 and 1 in this version are the same, and we will not need to insert the same element twice.*

*NOTE 2: If you have the cards mentioned in the introduction, now is a good chance to use them and visualize each approach for yourself (one distinct color for each container). In case you do not have any at hand, I will attach some pictures at the [Pictures](#insertion-methods) section.*

**First approach - inserting left to right**

You go to the 1st element of the sorted container - let's name it A<sub>1</sub>, and *select its pair* from the unsorted one - name that B<sub>1</sub>. Because you know that B<sub>1</sub> is smaller than its pair, and you also know that A<sub>1</sub> is the smallest in the unsorted container, you need 0 comparisons to insert B<sub>1</sub>. Now you move on to A<sub>2</sub> (which now has been promoted to index 3, but we always only care about the original index) and insert its pair (B<sub>2</sub>). Again, you only need to compare B<sub>2</sub> with the elements *left from* A<sub>2</sub>, because you know that its smaller than A<sub>2</sub>, and everything right from A<sub>2</sub> is bigger than A<sub>2</sub>. But because you always insert left-side from your current index, each insertion will, with 100% certainty, increase the number of elements you need to perform the search on in the next turn. When you arrive to the last B to insert, you will need to do binary insertion on a container of 20 elements (from the total of 22, excluding the pair of B<sub>11</sub> and B<sub>11</sub> itself).

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

If you observe the above table, you can see what the Jacobstahl sequence does beautifully. Table 1 shows that the amount of comparisons needed always increases at a field size of the next power of 2 (for example, there is an increase in comparisons at 1, 4, 8, and 16 elements). Jacobstahl *keeps your search field size just below this treshold, for as long as possible*. Since beginning from 2<sup>n</sup> elements you would have a required comparison number increase, you can be sure as hell your n<sup>th</sup> search field size will be *exactly* 2<sup>n</sup> - 1.

How does this happen? Maybe you remember from the beginning that if you know a Jacobstahl number with the index of _k_, you can always calculate the next one with the formula J<sub>k + 1</sub>  =  2<sup>k + 1</sup>  -  J<sub>k</sub>. You can reorganize this to J<sub>k</sub> + J<sub>k + 1</sub> =  2<sup>k + 1</sup>, which means, as you go from left to right, any 2 neighbors of the sequence will always give you the next power of 2. If you look at the first few Jacobstahl numbers (**1, 3, 5, 11, 21, 43, 85, 171**), you can observe this pattern very clearly.

This is important becase when you start insertion from any given Jacobstahl index, your search field size will be made of the current Jacobstahl number (all the As concerned until this index) and the previous one (all the Bs already inserted). For example, when I'm starting to insert from the Jacobstahl index of 5, my search field in the "bigger" container consists of 8 elements: 5 As were already there, and so far 3 Bs got inserted. This pattern will always give you the sum of two neighboring Jacobstahls, which always adds up to the next power of 2. But since at insertion your own pair never needs to be a part of your search field, you can go below this number by 1 - and like this you get your ideal search field size.

So in short, **this** is why Jacobstahl is crazy optimized for binary insertion.

### But how to keep track of my pairs?

In my above examples, you could see perhaps the biggest challenge one can face when implementing the algorithm. Remember that in **step 1**, we had to create pairs. When it comes to **step 3**, the insertion phase, you need to strongly rely on these pairs, because when it comes to the binary insertion, each B gets inserted *left from* its pair, and everything right from its pair can be ignored. If we don't keep track of the pairs, each B needs to be inserted *on a search field covering the whole container A*. This means more comparisons than any of the approaches listed before.

But there are multiple levels of recursion between most step 1s and corresponding step 3s. Let's say you have a container of 22 elements, separating it into 11 As and 11 Bs is the very first step in your algorithm. Merging the 11 Bs into the now-sorted As should be the very last. It's easy to say "pick an A and find its pair" - but how to know which B used to belong to it?

The first and most important thing I want to say about this: **DO NOT use std::find for this purpose!**

This approach includes not taking duplicates, then for every A, saving what your original B was at **step 1**, and using `std::find` to find it in the unsorted container when you arrive at **step 3** (this could return in a false positive if you take duplicates, hence the exclusion). A lot of people do this, but it's wrong, and is completely against the purpose of the algorithm.

Like I mentioned earlier, the point of merge insertion is sorting your elements with the least amount of comparisons between any two `T`. `std::find`, while searching, will iterate through the unsorted container, - on each turn comparing two `T` which each other, which could be completely avoided, had we kept proper track of the relationship between As and Bs from the beginning. Remember that our base assumption is that comparing any two `T` is a very expensive operation. A properly implemented Ford-Johnson should therefore have no issue with duplicates.

Another thing that I find important to address here: for a long time, there was a widespread belief on campus about `std::find` performing binary search to find its target. **This is false**.

Binary search can not be performed on a container that is not sorted (at least it will not lead to any meaningful result). Instead, `find` iterates element by element (thus has linear complexity). Therefore using it for the binary insertion phase (finding where exactly to insert within your custom boundaries) is also wrong, and leads to a massive amount of redundant comparisons. I have heard of some people overloading `find` or using `lower_bound` instead (there is also a `binary_search` function in the STL). Personally I would recommend you to write your own binary search algorithm to better understand the process - this will then also enable you to count your comparisons (which I will talk about in a later section).

But it's very important to clarify that using `std::find` either for insertion or to find which B belongs to a certain A **is not acceptable**.

There are many other ways to tackle the latter, although this is arguably the hardest part of any implementation. [Xaver](https://github.com/rwxg) had a solution using `std::pair`s and "ancestor pointers" pointing at the pairs they were derived from. [Ismayil](https://github.com/ismayilguliyev28) stored each `T` together with their index in the original container, then used this information to look up the ancestor pairs of each element at every step 3 (since index is not of type `T`, going through a container to look for a specific index is fine). I also know [Michi](https://github.com/HeiMichael) treats groups of `T` that have ever been compared as one unit that moves together, and then always compares the "top" element of two units with each other (see picture).

<div align="center">
<img src="/resources/imgs/groups.jpg" width="600">

  Grouping approach. After 3rd comparison we have arrived at **step 3** for the first time.
</div>

I learned the approach I follow from [Mohamad](https://github.com/zolfagharipour) during an evaluation. I call it "mirroring" because it includes using multiple pairs of containers on each level - one of them "canonical", and all the others mirroring what happens in the first pair. The main idea behind this is that at the first separation, the pairs are aligned in a way that index 0 in container A will be the pair of index 0 in container B. However, the alignment of container A changes in the process of sorting, so we have to make sure that the alingment of container B changes in the exact same way - then the pairs will end up again correctly aligned (bearing the same index) before the final insertion. (Of course insertion itself will then change the indexes, so the implementation will have to account for that). Because this is the approach I know the best, for the ones interested, I have made a short documentation of the main idea using Ligretto cards and put it in the [Pictures](#pictures) section.

### Testing if your implementation is correct

In the final part of this tutorial, I want to give some tips on how to test if your implementation is done correctly.

The subject requires us to print a very specific output (container content after sorting and time). But based on that output alone, it is impossible to determine if the sort was correctly implemented. You could implement bubble sort and still end up with a sorted sequence of numbers in the end. Or you could start with two containers, one empty, one full, then do pure binary insertion from one to the other and even the time will not tell you are doing something different. These are of course very extreme examples which would probably not pass an evaluation (in case the code is checked), but you could still do something *very similar* to merge insertion which still works different here and there.

The only way to *really* check if you have done it the right way is through checking the number of comparisons you make while you sort.

You can put a counter for comparisons in your code, and every time you check for `<`/ `>` / `=` *between any two `T`* (this is again important), you increment it. This mostly happens between comparing the assigned pairs and doing the binary insertion. Therefore to be able to do this, you have to have your own function (or overload) written for the binary search phase. Once you have your number printed, you can use this table from the book (page 186) to check if the amount of comparisons is below the required treshold or not.

<div align="center">
   <br>
<img src="/resources/imgs/table.png" width="600">

  Table of worst-case comparisons for elements up to 33
</div>

This is calculated up to 33, but the book provides the formula for calculating it for any (n) number of elements:

<div align="center">
   <br>
<img src="/resources/imgs/formula.png" width="150">
</div>

<br>

I have made a tiny executable that will calculate you the worst-case comparisons for most n (in the `resources` folder), but anyway I put it into a table up till the first 100, in case some of you might need it.

<table>
  <tr>
    <th>Elements<br>n</th>
    <td>34</td>
    <td>35</td>
    <td>36</td>
    <td>37</td>
    <td>38</td>
    <td>39</td>
    <td>40</td>
    <td>41</td>
    <td>42</td>
    <td>43</td>
    <td>44</td>
    <td>45</td>
    <td>46</td>
    <td>47</td>
    <td>48</td>
    <td>49</td>
    <td>50</td>
    <td>51</td>
    <td>52</td>
    <td>53</td>
    <td>54</td>
    <td>55</td>
    <td>56</td>
    <td>57</td>
    <td>58</td>
    <td>59</td>
    <td>60</td>
    <td>61</td>
    <td>62</td>
    <td>63</td>
    <td>64</td>
    <td>65</td>
    <td>66</td>
    <td>67</td>
    <td>68</td>
    <td>69</td>
    <td>70</td>
    <td>71</td>
    <td>72</td>
    <td>73</td>
    <td>74</td>
    <td>75</td>
    <td>76</td>
    <td>77</td>
    <td>78</td>
    <td>79</td>
    <td>80</td>
    <td>81</td>
    <td>82</td>
    <td>83</td>
    <td>84</td>
    <td>85</td>
    <td>86</td>
    <td>87</td>
    <td>88</td>
    <td>89</td>
    <td>90</td>
    <td>91</td>
    <td>92</td>
    <td>93</td>
    <td>94</td>
    <td>95</td>
    <td>96</td>
    <td>97</td>
    <td>98</td>
    <td>99</td>
    <td>100</td>
  </tr>
  <tr>
    <th>Comparisons<br>F(n)</th>
    <td>131</td>
    <td>136</td>
    <td>141</td>
    <td>146</td>
    <td>151</td>
    <td>156</td>
    <td>161</td>
    <td>166</td>
    <td>171</td>
    <td>177</td>
    <td>183</td>
    <td>189</td>
    <td>195</td>
    <td>201</td>
    <td>207</td>
    <td>213</td>
    <td>219</td>
    <td>225</td>
    <td>231</td>
    <td>237</td>
    <td>243</td>
    <td>249</td>
    <td>255</td>
    <td>261</td>
    <td>267</td>
    <td>273</td>
    <td>279</td>
    <td>285</td>
    <td>291</td>
    <td>297</td>
    <td>303</td>
    <td>309</td>
    <td>315</td>
    <td>321</td>
    <td>327</td>
    <td>333</td>
    <td>339</td>
    <td>345</td>
    <td>351</td>
    <td>357</td>
    <td>363</td>
    <td>369</td>
    <td>375</td>
    <td>381</td>
    <td>387</td>
    <td>393</td>
    <td>399</td>
    <td>405</td>
    <td>411</td>
    <td>417</td>
    <td>423</td>
    <td>429</td>
    <td>436</td>
    <td>443</td>
    <td>450</td>
    <td>457</td>
    <td>464</td>
    <td>471</td>
    <td>478</td>
    <td>485</td>
    <td>492</td>
    <td>499</td>
    <td>506</td>
    <td>513</td>
    <td>520</td>
    <td>527</td>
    <td>534</td>
    
  </tr>
</table>

<br>

Because you are sorting random numbers, some sequences you get can be easier to sort than others (imagine a container made of 1, 1, 1, 1, 1 - at the binary insertion step, every number gets immediately inserted after at most 1 comparison). The tables only show the worst amount of comparisons - *F(n)* - for a given number of members (*n*). This means sometimes you will get this number, sometimes you will go below this number - but given your numbers are *reasonably random* (so not like in my previous example), *you should not go significantly below the treshold*. If you generate a container of 21 numbers, and you happen to sort it with just 42 comparisons, then instead of having greatly optimized merge insertion, you are probably not counting your comparisons right.

Another thing that should also never happen is exceeding the treshold - even in very rare cases, even if just by 1. This *always* means something is not correct in your code. 

You can, for example, take this script from the subject: `` ./PmergeMe `shuf -i 1-100000 -n 21` ``. This will shuffle all numbers between 1 and 100000 and cut it short after the first 21 (so will give you a list of 21 random elements between 1 and 100k, no duplicates in this case). Here is a stupid but simple modification if you want some reasonable amount of random duplicates: `` ./PmergeMe `shuf -i 1-21 -n 11; shuf -i 1-21 -n 10` ``.

You need to be able to spam this command, sort correctly *and* never exceed the worst-case comparisons (66 in this case), no matter how many times you do it. Also with different amount of elements, big and small alike. If you notice any anomaly, you need to stop there and address that, because it always signals a bug and will help you make your code better. What I always did in this case is getting that exact sequence that caused the issue (only the *order* of elements in the input matters, so you can use the indexes instead of the random numbers themselves), make my program print what it does at each step, then manually do the sorting with the cards and compare the two for any differences. The whole debugging phase was really just an endless loop of doing this until everything finally checked out.

[UPDATE] Now you can also find a tiny automated [tester](#tester) in this repo for testing various input.

In case you want to show the comparison numbers during evaluation, I recommend using conditional compilation to not have to change your code, since the subject is very strict about the looks of the expected output. If you don't know how this works, check how you modified `BUFFER_SIZE` at compilation in `get_next_line` - you have to do the exact same thing for a macro of your choice, which then you can check before printing. While a counter can also be added manually during evaluation, proper testing requires it to be set up beforehand anyway.

I have to say that I find the subject of this exercise very misleading for multiple reasons. First of all, it leaves up to your implementation if you want to accept duplicates or not, even though any approach that *has a reason* not to take them is probably faulty. Secondly, it does not require you to count the number of your comparisons, and asks you to use *timing* instead, as if entirely missing the point of the algorithm. One can still argue that timing can show the difference between how different containers operate - this could be a valid point, *if the subject would not encourage you to write differently optimized code for different containers*. If my code for sorting is different for container of type A and container of type B, then it makes no sense to attribute the time difference between the two sorts to differences in how the containers operate internally. (For this reason, I decided to use templates despite of subject recommendation).

My opinion on the topic is that even though the subject does not ask for it, if someone can not provide any proof of counting the comparisons in their code, regardless of their implementation being wrong or right - it means they do not understand the purpose of and the main idea behind merge insertion. This might sound strict, and if we are honest, this project can truly be a pain to research and implement. It relies heavily on theory, it's recursive, and it needs a lot of trial and error to work _just right_. But once it does, it gives you a lot of pride that you have done it. By this point, I hope to have convinced a few of you that the Ford-Johnson is cool, and it's really worth the effort you need to put into it.

<br>

## Pictures

<div align="center">

### Mirroring approach

</div>

<div align="center">
<img src="/resources/imgs/mirroring/1.jpg" width="600">

  Full container of 9 unsorted elements. Pairs marked with matching colors.
</div>

<div align="center">
<img src="/resources/imgs/mirroring/2.jpg" width="600">

  Smaller elements separated into container 2. Pairs still marked with matching colors. <br>Container 1 is now canonical and container 2 will mirror container 1 at the next step of separation.<br>Elements without pairs always move to the bottom.
</div>

<div align="center">
<img src="/resources/imgs/mirroring/3.jpg" width="600">

  Smaller elements of container 1 separated into container 3.<br> Container 2 mirrors container 1 (thus creating container 4).<br> No actual comparison happens there (you can see that container 4 <br>does not necessarily contain the smaller elements). <br>Elements without pairs always move to the bottom.
</div>

<div align="center">
<img src="/resources/imgs/mirroring/4.jpg" width="600">

  Container 1 still canonical. Containers 2, 3 and 4 follow the separation pattern<br> (index 0 goes down). Elements without pairs always move to the bottom.
</div>

<div align="center">
<img src="/resources/imgs/mirroring/5.jpg" width="600">

  Step 3 for the first time. Container 5 got merged into 1. Only this merge is canonical. <br>6, 7 and 8 got merged into 3, 2 and 4 copying the canonical pattern. <br>Elements without pairs get inserted to the end.
</div>

<div align="center">
<img src="/resources/imgs/mirroring/6.jpg" width="600">

  Step 3 for the second time. Container 3 got merged into 1. Canonical merge got copied by containers 2 and 4.<br> You can now see the point of mirroring: the pairs from the original container have been retained (marked with same color).<br> Each A has the same index as its B, but container A is now sorted. We are ready for the final binary insertion.
</div>

<br>

<div align="center">

### Insertion methods

</div>

<div align="center">

<img src="/resources/imgs/insertion/before.jpg" width="600">

  Two containers of 11 elements each, before insertion step.<br> Upper container sorted, lower unsorted, pairs have the same index.
</div>

<div align="center">

<img src="/resources/imgs/insertion/forward.jpg" width="600">

  <b>Inserting left to right (approach 1)</b>.<br> Third element to insert has a search field of 4 (3 comparisons).
</div>

<div align="center">

<img src="/resources/imgs/insertion/backward.jpg" width="600">

  <b>Inserting right to left (approach 2)</b>.<br> Third element to insert has a search field of 10 (4 comparisons).<br>
  White cards are used as placeholders to retain indexes of pairs.
</div>

<div align="center">

<img src="/resources/imgs/insertion/jacobstahl.jpg" width="600">

  <b>Inserting according to Jacobstahl sequence (approach 3)</b>.<br> Third element to insert has a search field of 3 (2 comparisons).
</div>

# Tester

We now have a tester for automated testing, which was contributed by Ismayil. It's a shell script which you can find in the `resources` folder. In order to use it, you need to compile your executable, and move it in the same folder where you have the tester. Then launch the tester with `./test.sh` and it will prompt you for configuration.

The tester tests for two things: if your executable sorts correctly (according to your output), and if your number of comparisons are below the required limit (for an input size up to 250). In order for it to work, you need to make sure that you print your number of comparisons in your output (for example, I need to `make count` for that). We have decided to make it put occasional duplicates in the input, therefore if your executable does not support that, it will not work correctly for you (but please check my reasoning above why I disagree with this approach).

It's a very impressive tester and it can be a lot of help, but I would still recommend you to do your manual tests in addition to it. Relying on a tester can sometimes make one *too* comfortable. For instance, this tester tests if you output the right amount of comparisons, but does not test if you have counted those comparisons right (and will not cry for a suspiciously low amount either). Therefore I recommend against using it during evaluations. Checking the code itself and discussing the implementation should be the most important part anyway. But it can be a very useful tool for regression tests (checking if fixing the sort for a certain input or refactoring some part of the code might have ruined the functionality for others).
