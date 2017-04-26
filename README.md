USEFUL COMMANDS

To combine multiple cards: 
combineCards.py Name1=card1.txt Name2=card2.txt .... > card.txt 

in particular:
combineCards.py Name1=combineCard_onShell_15p9ifb_eeee.txt Name2=combineCard_onShell_15p9ifb_mmmm.txt 
Name3=combineCard_onShell_15p9ifb_eemm.txt > combinedCard.txt

To run the likelihood analysis:
Run with: combine -M ProfileLikelihood --significance combineCard_eeee.txt -t -1 --expectSignal=1 -S 0 --toysFreq

candTree->Print("*LHEwe*")
