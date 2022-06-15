for ( j = 0; j < i-1; j++)
        {
            for ( k = 0; k < i-j-1; k++)
            {
                if (mhs[k].nim>mhs[k+1].nim)
                {
                    temp = mhs[k];
                    mhs[k] = mhs[k+1];
                    mhs[k+1] = temp;
                }
            }
        }