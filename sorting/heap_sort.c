void downheap(int cur, int k)
{
  int left, right, p;
    while(cur < k) {
      left = cur * 2 + 1;
      right = cur * 2 + 2;and t

      if (left >= k && right >= k) break;

      p = cur;
      if (left < k && data[p] < data[left]) {
        p = left;
      }
      if (right < k && data[p] < data[right]) {
        p = right;
      }
      if (p == cur) break;

      swap(&data[cur],&data[p]);
      cur=p;
    }
}

void heapify(int n)
{
  int i,p;
  for(i = (n-1)/2; i >= 0; i--){
    downheap(i,n);
  }
  //for(i=0;i<size;++i)printf("%d ",data[i]);
  //printf("\n");
}

void heap()
{
  int k;
  heapify(size);
  for(k = size-1; k > 0; ){
    swap(&data[0],&data[k]);
    //k--;
    downheap(0,k);
    k--;
  }
}