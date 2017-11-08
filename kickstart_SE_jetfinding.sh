# do you really want to submit a thousand jobs by hand? 
# no you don't - so here's a little helper script


files=(137431 137546 137718 138275 138621 138872 139328 137432 137549 137722 138364 138624 139028 139329 137434 137595 137724 138396 138638 139029 139360 137161 137439 137608 137751 138438 138652 139036 139437 137162 137440 137638 137752 138439 138653 139037 139438 137230 137441 137639 137844 138442 138662 139038 139465 137231 137443 137685 137848 138469 138666 139105 139503 137232 137530 137686 138190 138534 138730 139107 139505 137235 137531 137691 138192 138578 138732 139173 139507 137236 137539 137692 138197 138579 138837 139309 139510 137243 137541 137693 138201 138582 138870 139310 137430 137544 137704 138225 138583 138871 139314)

cen=(0 5)
per=(40 50)

for ((i = 0; i < ${#files[@]}; ++i)); do
    for ((k = 0; k < ${#cen[@]}-1; ++k)); do
        inck=$(( $k + 1 ))
        ./bsub_SE_jet_analysis.sh ${cen[$k]} ${cen[$inck]} ${files[$i]}
        ./bsub_SE_jet_analysis.sh ${per[$k]} ${per[$inck]} ${files[$i]}
#        ./resubmit.sh ${cen[$k]} ${cen[$inck]} ${files[$i]}
    done
done
