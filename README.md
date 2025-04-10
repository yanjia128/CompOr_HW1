# CompOr_HW1

1-1. buble sort
這次作業以address register取代c code pointer寫法，看完講義後，可以寫出一點像樣的，最後交給AI老師幫我修理程式，就完成拉
1-2. array search
從這邊有學到輸入輸出operand中"=r"以及"r"的差異，在寫過第一題後直接套用一樣的方式處理pointer，用c code來翻譯，是不錯的做法
1-3. linked list sort
這次有用到gpt生出一定的架構，再自行debug。先寫Block C，一開始沒有注意到pointer站的資源所以offset寫錯，還打印出c code中pointer的memory address，觀察後發現這跟assembly code中所用的address不一樣，翻了講義，才解決這個問題
第二步，寫block B（split list），修改好pointer的offset，看了一下大概邏輯與c code語意相近，就沒問題了。最後，處理最麻煩的部分(merge list)，一樣先以c code 過compile，再將程式轉換成assemly code，問題點跟前一步雷同。
