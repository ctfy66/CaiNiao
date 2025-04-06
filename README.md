# CaiNiao

# 简易使用 git 教学

## 安装 Git：

首先，下载并安装 Git 客户端，可以从 Git 官方网站 下载适合操作系统的版本。
配置 Git：

安装完成后，需要配置 Git 的用户信息，这些信息将用于提交记录。
```
git config --global user.name "你的名字"
git config --global user.email "你的邮箱"
```
## 克隆仓库：

从远程仓库克隆项目到本地。
```
git clone https://github.com/ctfy66/CaiNiao.git
```
## 创建分支：

在开发新功能或修复 bug 时，建议创建一个新的分支。
```
git checkout -b 新分支名称
```
添加和提交更改：

在本地进行代码修改后，添加和提交这些更改。
```
git add .
git commit -m "提交信息"
```
推送分支到远程仓库：

将本地分支推送到远程仓库。
```
git push origin 新分支名称
```
## 创建 Pull Request：

在 GitHub 上创建 Pull Request，发起代码审查并请求合并代码到主分支。
合并代码：

经过代码审查后，合并 Pull Request 到主分支。
更新本地仓库：

## 定期同步远程仓库的最新更改到本地。
```
git pull origin main
```
这些是使用 Git 进行合作的一些基础步骤，掌握这些流程后，可以帮助团队成员更高效地协作开发项目。
