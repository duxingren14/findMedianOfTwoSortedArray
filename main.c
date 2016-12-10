int max(int a, int b){
    return a>b?a:b;
}
int min(int a, int b){
    return a<b?a:b;
}
double  findMedian(int *nums1,int left1,int right1, int *nums2, int left2, int right2,int numBelowMedian,int numAboveMedian){
    //printf("%d %d ", numBelowMedian, numAboveMedian);
    if( left1 <= right1 && left2<= right2){
        if(numBelowMedian == 0 && numAboveMedian ==0) {
            return (nums1[left1] + nums2[left2])/2.0;
        }else if(numAboveMedian ==1){
            int flag = nums2[right2] > nums1[right1];
            return findMedian(nums1,left1,right1- !flag,nums2, left2, right2-flag,
                numBelowMedian, 0);
        }else if(numBelowMedian ==1){
            int flag = nums2[left2] < nums1[left1];
            return findMedian(nums1,left1 + !flag,right1,nums2, left2 + flag, right2,
                0, numAboveMedian);
        }else{
            int mid1 = (left1+right1)/2;
            int mid2 = (left2+right2)/2;
            int new_left, new_right;
            if(nums1[mid1] < nums2[mid2]){
                new_left = left1; new_right = right2;
                if( numBelowMedian > mid1-left1 + mid2-left2) new_left = mid1+1;
                else if( numBelowMedian == mid1-left1 + mid2-left2) new_left = mid1;
                if( numAboveMedian > right1 - mid1 + right2 - mid2) new_right = mid2-1;
                else if( numAboveMedian == right1 - mid1 + right2 - mid2) new_right = mid2;
                return findMedian(nums1,new_left,right1,nums2, left2, new_right,
                numBelowMedian - new_left + left1, numAboveMedian + new_right - right2);
            }else{
                new_left = left2; new_right = right1;
                if( numBelowMedian > mid1-left1 + mid2-left2) new_left = mid2+1;
                else if( numBelowMedian == mid1-left1 + mid2-left2) new_left = mid2;
                if( numAboveMedian > right1 - mid1 + right2 - mid2) new_right = mid1-1;
                else if( numAboveMedian == right1 - mid1 + right2 - mid2) new_right = mid1;
                return findMedian(nums1,left1,new_right,nums2, new_left, right2,
                numBelowMedian - new_left + left2, numAboveMedian + new_right - right1);
            }
        }
    }
    int * nums = NULL;
    int left , right;
    if(left2 > right2){
        nums = nums1;left = left1;right = right1;
    }else if(left1 > right1){
        nums = nums2;left = left2; right = right2;
    }
    if(numBelowMedian == 0 && numAboveMedian ==0) {
        return (nums[left]+nums[right])/2.0;
    }else{
        int new_left = left + numBelowMedian;
        int new_right = right - numAboveMedian;
        return findMedian(nums,new_left,new_right,nums2, right2 + 3, right2,
        numBelowMedian - new_left + left, numAboveMedian + new_right - right);
    }
    
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int num = (nums1Size+nums2Size-1)/2;
    return findMedian(nums1,0,nums1Size-1,nums2, 0, nums2Size-1, num, num);
}
