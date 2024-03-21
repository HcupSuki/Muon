Just a Test for Muon trajectories rebuilding work.

1.分支创建
$ git switch -c dev

-b表示创建并切换，相当于以下两条命令：

$ git branch dev
$ git checkout dev
Switched to branch 'dev'

2.展示已有分支
$ git branch

3.切换分支
$ git switch main

4.合并分支
$ git merge test

5.删除分支
$ git branch -d dev

6.合并并保留合并信息
$ git merge --no-ff -m "merge with no-ff" dev

--no-ff为禁用快速合并参数，可以保留合并信息
-m给commit写注释

查看
$ git log --graph --pretty=oneline --abbrev-commit

7.未提交时暂时保存工作

$ git stash

提取

1）提取后stash删除
$ git stash pop

2）提取后stash不删除
$ git stash apply

查看
$ git stash list

8.复制一次提交到当前分支

$ git cherry-pick 4c805e2（想要复制的提交的密钥，可以使用git log得到）

9.如果要丢弃一个没有被合并过的分支，可以强行删除
$ git branch -D <name>

10.显示远程库更详细的信息
$ git remote -v

11.因此，多人协作的工作模式通常是这样：

首先，可以试图用git push origin <branch-name>推送自己的修改；

如果推送失败，则因为远程分支比你的本地更新，需要先用git pull试图合并；

如果合并有冲突，则解决冲突，并在本地提交；

没有冲突或者解决掉冲突后，再用git push origin <branch-name>推送就能成功！

如果git pull提示no tracking information，则说明本地分支和远程分支的链接关系没有创建，用命令git branch --set-upstream-to <branch-name> origin/<branch-name>。

这就是多人协作的工作模式，一旦熟悉了，就非常简单。
