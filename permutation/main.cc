#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

// (1) 从右向左，找出第一个比右边数字小的数字A。
// (2) 从右向左，找出第一个比A大的数字B。
// (3) 交换A和B。
// (4) 将A后面的串（不包括A）反转。

template < class T > bool next_perm(T * start, T * end)
{
    //_asm{int 3}
    if (start == end) {
	return false;
    } else {
	T *pA = NULL, *pB;
	T tmp = *end;

	// find A.
	for (T * p = end; p >= start; p--) {
	    if (*p < tmp) {
		pA = p;
		break;
	    } else {
		tmp = *p;
	    }
	}

	if (pA == NULL) {
	    return false;
	}
	// find B.
	for (T * p = end; p >= start; p--) {
	    if (*p > *pA) {
		pB = p;
		break;
	    }
	}

	// swap A, B.
	tmp = *pA;
	*pA = *pB;
	*pB = tmp;

	// flip sequence after A
	for (T * p = pA + 1, *q = end; p < q; p++, q--) {
	    tmp = *p;
	    *p = *q;
	    *q = tmp;
	}
	return true;
    }
}

// 使用0或1表示集合中的元素是否出现在选出的集合中，因此一个0/1列表即可表示选出哪些元素。
// 例如：[1 2 3 4 5]，选出的元素是[1 2 3]那么列表就是[1 1 1 0 0]。
// 算法是这样的：
// comb(set, n, k)
// {
//     (1) 从左到右扫描0/1列表，如果遇到“10”组合，就将它转换为”01”.
//     (2) 将上一步找出的“10”组合前面的所有1全部移到set的最左侧。
//     (3) 重复(1) (2)直到没有“10”组合出现。
// }


template<class T>
void combine(T set[], int n, int k, void (*cbk)(T set[]))
{
    unsigned char * vec = new unsigned char[n];
    T * subset = new T[k];
     
    // build the 0-1 vector.
    for(int i = 0; i < n; i++)
    {
        if (i < k)
            vec[i] = 1;
        else
            vec[i] = 0;
    }
     
    // begin scan.
    bool has_next = true;
    while (has_next)
    {
        // get choosen.
        int j = 0;
        for (int i = 0; i < n; i++)
        {
            if (vec[i] == 1)
            {
                subset[j++] = set[i];
            }
        }
        cbk(subset);
         
        has_next = false;
        for (int i = 0; i < n - 1; i++)
        {
            if (vec[i] == 1 && vec[i + 1] == 0)
            {
                vec[i] = 0;
                vec[i + 1] = 1;
                 
                // move all 1 to left-most side.
                int count = 0;
                for (int j = 0; j < i; j++)
                {
                    if (vec[j] == 1)
                        count ++;
                }
                if (count < i)
                {
                    for (int j = 0; j < count; j++)
                    {
                        vec[j] = 1;
                    }
                    for (int j = count; j < i; j++)
                    {
                        vec[j] = 0;
                    }
                }
 
                has_next = true;
                break;
            }
        }
    }
    delete [] vec;
    delete [] subset;
}
int main()
{
	char filename[] = "rank10.txt";
	ofstream fout(filename);
    int myints[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    cout << "The 3! possible permutations with 3 elements:\n";

    sort(myints, myints + 9);

    do {
	// cout << myints[0] << " " << myints[1] << " " << myints[2] << " "
	// 	<< myints[3] << " " << myints[4] << " " << myints[5] << " "
	// 	<<myints[6] << " " << myints[7] << " " << myints[8] << " "
	// 	<<myints[9] << endl;
	fout << myints[0]  << myints[1]  << myints[2] 
		<< myints[3]  << myints[4]  << myints[5] 
		<<myints[6]  << myints[7]  << myints[8]
		<<myints[9] << endl;
    //} while (next_permutation(myints, myints + 3));
    } while (next_perm(myints, myints + 9));

    return 0;
}
