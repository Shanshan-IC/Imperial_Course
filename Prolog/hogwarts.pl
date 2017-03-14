
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%                       CS518: Assesment 1                    %%%%%%%%%
%%%%%%%%%               Magdalena Sadowska, CID: 01095948             %%%%%%%%%
%%%%%%%%%            Program that analyses MSc Magic degree           %%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FACTS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% the students in Hogwarts:
student(hp, 'Harry James Potter', gryffindor).
student(hg, 'Hermione Jean Granger', gryffindor).
student(rw, 'Ronald Weasley', gryffindor).
student(ms, 'Magdalena Sadowska', gryffindor). 	% adding myself(Q1)
student(ll, 'Luna Lovegood', ravenclaw).
student(cc, 'Cho Chang', ravenclaw).
student(tb, 'Terry Boot', ravenclaw).
student(ha, 'Hannah Abbott', hufflepuff).
student(cd, 'Cedric Diggory', hufflepuff).
student(nt, 'Nymphadora Tonks',hufflepuff).
student(dm, 'Draco Malfoy', slytherin).
student(gg, 'Gregory Goyle', slytherin).
student(vc, 'Vincent Crabbe', slytherin).

% the teachers in Hogwarts:
teacher(ad, 'Albus Percival Wulfric Brian Dumbledore').
teacher(ff, 'Filius Flitwick').
teacher(rh, 'Rubeus Hagrid').
teacher(gl, 'Gilderoy Lockhart').
teacher(rl, 'Remus John Lupin').
teacher(mm, 'Minerva McGonagall').
teacher(qq, 'Quirinus Quirrell').
teacher(ss, 'Severus Snape').
teacher(ps, 'Pomona Sprout').
teacher(st, 'Sibyll Patricia Trelawney').
teacher(mh, 'Madam Hooch').
teacher(as, 'Aurora Sinistra').
teacher(cub, 'Cuthbert Binns').
teacher(bb, 'Bathsheba Babbling').
teacher(sv, 'Septima Vector').
teacher(chb, 'Charity Burbage').
teacher(wt, 'Wilkie Twycross').

% compulsory courses for the MSc in Magic:
compCourse(astro, 'Astronomy', as).
compCourse(charms, 'Charms', ff).
compCourse(defence, 'Defence against the Dark Arts', qq).
compCourse(fly, 'Flying', mh).
compCourse(herb, 'Herbology', ps).
compCourse(history, 'History of Magic', cub).
compCourse(potions, 'Potions', ss).
compCourse(trans, 'Transfiguration', mm).

% optional courses for the MSc in Magic
optCourse(runes, 'Study of Ancient Runes', bb).
optCourse(arith, 'Arithmancy', sv).
optCourse(muggle, 'Muggle Studies', chb).
optCourse(creatures, 'Care of Magical Creatures', rh).
optCourse(div, 'Divination', st).
optCourse(app, 'Apparition', wt).
optCourse(choir, 'Frog Choir', ff).
optCourse(quid, 'Quidditch', mh).

% optional courses chosen by particular students - ordered depth-first: (Q2)
enrolled_opt(hp, runes).
enrolled_opt(hp, div).
enrolled_opt(hp, quid).
enrolled_opt(hg, runes).
enrolled_opt(hg, div).
enrolled_opt(hg, creatures).
enrolled_opt(hg, quid).
enrolled_opt(hg, choir).
enrolled_opt(hg, app).
enrolled_opt(rw, muggle).
enrolled_opt(rw, creatures).
enrolled_opt(rw, div).
enrolled_opt(ll, runes).
enrolled_opt(ll, choir).
enrolled_opt(ll, quid).
enrolled_opt(cc, runes).
enrolled_opt(cc, arith).
enrolled_opt(cc, choir).
enrolled_opt(tb, div).
enrolled_opt(tb, app).
enrolled_opt(tb, choir).
enrolled_opt(ha, muggle).
enrolled_opt(ha, choir).
enrolled_opt(ha, quid).
enrolled_opt(cd, arith).
enrolled_opt(cd, creatures).
enrolled_opt(cd, choir).
enrolled_opt(nt, runes).
enrolled_opt(nt, creatures).
enrolled_opt(nt, div).
enrolled_opt(dm, runes).
enrolled_opt(dm, arith).
enrolled_opt(dm, muggle).
enrolled_opt(gg, arith).
enrolled_opt(gg, creatures).
enrolled_opt(gg, app).
enrolled_opt(vc, arith).
enrolled_opt(vc, creatures).
enrolled_opt(vc, app).
enrolled_opt(ms, arith).
enrolled_opt(ms, creatures).
enrolled_opt(ms, app).

% Hogwart houses: (helper facts for Questions 8-9:
house(gryffindor).
house(hufflepuff).
house(ravenclaw).
house(slytherin).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% RULES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Question 3:
% student with a particular id (SID) is enrolled on the course with short name (SCN):
enrolled(SID, SCN) :-
        student(SID, _, _),
        (compCourse(SCN, _, _) ; enrolled_opt(SID, SCN)).


% Question 4:
% a particular wizard (TN) teaches a particular course (SCN):
teaches(TN, SCN) :-
        (teacher(TID, TN), optCourse(SCN, _, TID));
        (teacher(TID, TN), compCourse(SCN, _, TID)).


% Question 5:
% student (SN) is enrolled on course that is taught by (TN):
taughtBy(SN, TN) :-
        (student(SID, SN, _), enrolled(SID, SCN)),
        teaches(TN, SCN).


% Question 6:
% student (SN) is enrolled on the optional course (CN):
takesOption(SN, CN) :-
        student(SID, SN, _),
        (enrolled_opt(SID, SCN),optCourse(SCN, CN, _)).


% Question 7:
% all courses (OptCourses) student (SN) is enrolled onto
% in alphabetical order:
takesAllOptions(SN, OptCourses) :-
        setof(CN, takesOption(SN, CN), OptCourses).


% Question 8:
% all student names (SN) that are sorted by student short name (SID):
replaceIDs([],[]).
        replaceIDs([H1|T1],[H2|T2]) :-
        student(H1,SN,_),
        H2 = SN,
        replaceIDs(T1, T2).

studentsInHouse(House, Students) :-
        findall(House, house(House), ListOfHouses),
        member(House, ListOfHouses),
        findall(SID, student(SID,_,House), UnsortedListOfIDs),
        sort(UnsortedListOfIDs, ListOfIDs),
        replaceIDs(ListOfIDs, Students).


% Question 9:
% all students per house (StudentsByHouse) that are enrolled on particular course (SCN/CN):
studentCourseListByHouse(SCN, House, Students) :-
        studentsInHouse(House, ListOfHouses),
        findall(SN,(enrolled(SID, SCN),student(SID, SN, _)), StudentCourses),
        findall(SN, (member(SN, ListOfHouses), member(SN, StudentCourses)), Students).

studentsOnCourse(SCN, CN, StudentsByHouse) :-
        (compCourse(SCN, CN, _);optCourse(SCN, CN, _)),
        findall(House-Students, studentCourseListByHouse(SCN, House, Students), StudentsByHouse).


% Question 10:
% all the student pairs (SN1, SN2) that share a particular course (CN):
sharedCourse(SN1, SN2, CN) :-
        takesOption(SN1, CN),
        takesOption(SN2, CN),
        SN1 \= SN2.


% Question 11:
% two different students (SN1, SN2) that are enrolled on exactly 3 same courses (Courses):
sharingStudents(SN1, SN2) :-
        student(_, SN1, _),
        student(_, SN2,_),
        SN1 \= SN2.

sameOptions(SN1, SN2, Courses) :-
        setof(CN, (sharedCourse(SN1, SN2, CN), sharingStudents(SN1, SN2)),Courses),
        length(Courses, N), N>=3.

