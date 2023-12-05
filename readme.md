# CS 2270 Git & GitHub Setup

## Overview

Welcome to your first CS 2270 assignment! This should help get you acquainted with the workflow of the coding assignments for this class. While the coding aspect of this assignment is trivial, the process that you need to follow is probably new to you. Understanding the workflow (and being able to pull it off!) is the main goal of this assignment. You'll need this to do all the remaining homework in the class. 

This is important enough that we'll explain the same workflow in several different ways. 

## Workflow

In general, the workflow for each assignment will be the same. I'll explain in words first, followed by the specific commands.

* First, you will click on a link in Moodle that will take you to a GitHub Classroom page. If you have not yet created your personal copy of that assignment's repository, it will invite you to create your copy. On the other hand if you've done it before, you'll see a link to your personal copy of the assignment. You only have to create this copy one time for each assignment. Pretty straightforward. The repository can only be viewed by you and the CS 2270 teaching team. Other students can't see your repo. You can view the contents of your repo by going to the link which was created for you upon accepting the assignment. 

* Now that you've created your git repository for the assignment, you can clone it. If you're not familiar with git and/or GitHub consider checking out the [git crash course](https://gist.github.com/johnsogg/56df0f970bd9e019da861fd37ceb42f8).

* Once you have your repository locally checked out (or to a web-based editor like Jupyterhub on CSEL), you can configure it for building and editing. This will involve setting up your editor and environment with the right tooling (Jupyterhub has this set up already). You'll only need to set up the tooling one time per computer, but you will need to configure each assignment one time when you first clone the repo.

* Then you can edit code! The specifics here differ per assignment, but the build/run process is the same. 

* When you're ready to submit your assignment, you'll get all your changes up to GitHub, copy the repository link, and submit it via the appropriate page in Moodle. A separate tool (called Inginious) will check out your repository, build the code and run the tests, and report results back to Moodle to be entered in the grade book. 

To summarize (this might not work for you right away - see below if that is the case):

```bash
$ git clone git@github.com:cu-cspb-2270-Fall-2023/pa9-johnsogg.git # clone your personal repo (for username 'johnsogg')
$ cd pa9-johnsogg/build # change directories into the repository's 'build' directory
$ cmake .. # configure for building. Note the two dots! Very important!
$ make # build your code
$ ./run_tests # execute the unit tests
$ ./run_app # execute an app, which doesn't do anything unless you program it to
```

Once you get used to doing this, it will become second nature.

## Annotated Directions (for CSEL / JupyterHub / VS Code)

You can work your assignments on your local computer, though this will require some setup that many of you will not want to deal with now. You can always get your local machine set up later, and we will help you do this if your setup is fairly normal.

Alternately, you can use the CSEL environment's JupyterHub to do everything. Here's how.

Create your personal copy of the assignment as described above.

1. Go to JuptyerHub in your browser by navigating to [https://coding.csel.io/](https://coding.csel.io/)

2. Choose the CSCI 2270 Data Structures environment

3. Select `File -> New -> Terminal`

4. Now you are ready to *clone* your repository from the remote GitHub repo to your local JupyterHub directory. You can do so by issuing the following command, replacing the SSH URL with your personal one. You can find your unique URL by clicking on the green *Code* icon on your GitHub page.  

```console
$ git clone https://github.com/cu-cspb-2270-Spring-2022/assignment-0-<your_github_handle>.git
```

 * You can also clone a repository within the JupyterHub graphical interface.  See video https://youtu.be/M293X5ssks4 for an example of cloning a repository using the built-in interface to Git.

5. At this point you can begin working with your code. We recommend that you use the VSCode editor environment. Go to `File -> New -> Launcher` and click on `VS Code IDE`. This opens a new browser tab.

6. Within VS Code, select `File -> Open Folder...` and then find the directory you just cloned and press OK. It should be `/home/jovyan/paN-homework-username`. In JupyterHub your username is always `jovyan`. This is unique to the CSEL environment. On your local machine it will be something else. New terminals will default to the folder you open.

7. Before we start writing any code, let's compile the starter code and see how we can run the executables.

    * Open up the terminal: `Terminal > New Terminal` (or use Control Backtick (the \` character))

    * Navigate to `build` directory:

    ```console
    $ cd build/
    ```  

    * Run `cmake` to set up the build environment (creates files in _build_ subdirectory that are needed to build the application). Note the double dots!
    
    ```console
    $ cmake ..
    ``` 
   
    * Now compile and build the executables:
   
    ```console
    $ make
    ``` 
    
    * Now we have two executable ready to run, `run_app` and `run_tests`

        * `run_app` is the executable that was build using your `/app` and `/code` source code files. You can use this to try a `Hello World` type of program to get familiar with the framework. 
        * `run_tests` is the executable containing the test cases that will be used for your assignment. Running this prior to solving any of the required problems should give you a score of 0.
        * Both executables will be located within the build directory, so run the following terminal command to execute:  

    ```console
    $ ./run_app
    ``` 
    
8. Each time you modify a source file (like `main.cpp`) you must rebuild the executables. 

    * Save your changes to disk. The compiler will only be able to use changes that have been saved to disk.
    * Issue the `make` command (must be run from the `build` directory). This will recompile the source files and rebuild the executables.
    * Run the application or run the tests with `./run_app` or `./run_tests`. Note the dot-slash before the executable name - this is important.

## Completing the Assignment

We intentionally made this part trivial. In the future assignments, the initial setup steps described above should only take a moment to complete for any assignment.  The bulk of your required work will be described in this section.

1. After running the application, determine what is being tested for this assignment See the __Test Cases__ section below.
2. Make a modification to the code to __Pass__ the test. (hint: each time you make changes to the code, be sure to save your edits to the code, _make_ the application with the new code, and then test the resulting application)
3. We suggest that you save your save the version of your code each time you get a test to pass. Make sure to save it both locally and on the GitHub server. 

### Checking code into GitHub

**Important:** one of the main advantages of using git and GitHub is that it gives you a very convenient way to back up your changes. For now, you will only need to know how to `add`, `commit`, and `push`.  (You are encouraged to learn further git commands throughout the semester.) Any time you get to a point where you want to save your code (for example, you got a function to pass a test case), do the following in the terminal:

1. Stage your changes for a commit. This means that any changes you want to save, need to be added explicitly. (Note that you have all kinds of files that are present in your repository. You only need to add the ones you have changed and want to save.) For example, let's say we want to stage the changes we made in `functions.cpp`. 
    ```console
    $ git add functions.cpp
    ```

2. Commit the changes to our local repository. The `-m` option allows you to add the required commit comment on the cmmand line.  Use a short comment that has meaning about what changes were made (e.g. "fixed output for test 2" or "added comments to all functions") 

    ```console
    $ git commit -m 'this is my first commit'
    ```

3. Finally, push the changes from your local version of the repo to the remote repo on GitHub. 

    ```console
    $ git push
    ```

You can run the above steps as many times as you want. Each time you commit/push your changes, a new commit number will be added to your repository. If ever you need to go back to a previous commit, you can do that with more advanced usage of the git tool.

### Test Cases

Open up the test code in the `/tests` directory to see what test cases you need to pass to get points on the assignment. For this assignment this is a file called `test_preview.cpp` but the exact name will differ from assignment to assignment. **It will be extremely useful for you to be able to read and understand what the test cases are doing.** You can learn from the unit tests and there are often hints contained in them (intentionally or otherwise).

#### Part 1

In `test_preview.cpp` scroll down until you find the test function labeled `TestFooA`. You can see that this is a unit test for the `fooA()` function. An assertion is used to check the output for correctness. Go to `/code/functions.cpp` to see if you can implement this function to return the correct output (again, this is intentionally trivial.) Once you have written the code and you want to check your solution, run `make` (remember to stay in the `build` directory). Then run the test executable `run_tests` and see if you pass the first test case. *If you are happy with your code, go ahead and run through the steps described above in the Checking code into GitHub section.*

#### Part 2

Now let's take a look at the next test case, `TestApp_1`. This one actually runs your `main()` function to check whether it prints the desired results in `stdout`. Look at the test case to see what the desired result needs to be, then go into `/app/main.cpp` and add the code to get a matching result.

## Submission

In order to submit your assignment, paste your GitHub repository link into the Inginious item for Assignment-0 provided on Moodle. Make sure you do submit your assignment prior to the deadline specified on Moodle. Inginious will pull the files from `code` and `app` directories and grade them using the same set of test cases as given in `test_preview.cpp`. 
