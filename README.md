# CompOr_HW1

1-1. buble sort
這次作業以address register取代c code pointer寫法，
1-2. array search

1-3. linked list sort
先寫Block C，一開始沒有注意到pointer站的資源所以offset寫錯，還打印出c code中pointer的memory address，觀察後發現這跟assembly code中所用的address不一樣，翻了講義，才解決這個問題
第二步，寫block B（split list），這次有用到gpt生出一定的架構，再自行debug，修改好pointer的offset，看了一下大概邏輯與c code語意相近，就沒問題了
