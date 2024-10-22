% Symptoms 
symptom(fever, flu).
symptom(cough, flu).
symptom(sore_throat, flu).
symptom(runny_nose, flu).
symptom(body_ache, flu).

symptom(frequent_urination, diabetes).
symptom(increased_thirst, diabetes).
symptom(weight_loss, diabetes).
symptom(fatigue, diabetes).

symptom(high_fever, dengue).
symptom(severe_headache, dengue).
symptom(pain_behind_eyes, dengue).
symptom(joint_muscle_pain, dengue).
symptom(rash, dengue).

symptom(fever, infection).
symptom(chills, infection).
symptom(body_ache, infection).
symptom(fatigue, infection).

ask_symptom(Symptom) :-
    write('Do you have '), write(Symptom), write('? (yes/no): '),
    read(Response),
    Response = yes.

check_flu(Patient) :-
    ask_symptom(fever),
    ask_symptom(cough),
    ask_symptom(sore_throat),
    ask_symptom(runny_nose),
    ask_symptom(body_ache),
    write(Patient), write(' might have flu.'),
    nl.

check_diabetes(Patient) :-
    ask_symptom(frequent_urination),
    ask_symptom(increased_thirst),
    ask_symptom(weight_loss),
    ask_symptom(fatigue),
    write(Patient), write(' might have diabetes.'),
    nl.

check_dengue(Patient) :-
    ask_symptom(high_fever),
    ask_symptom(severe_headache),
    ask_symptom(pain_behind_eyes),
    ask_symptom(joint_muscle_pain),
    ask_symptom(rash),
    write(Patient), write(' might have dengue.'),
    nl.

check_infection(Patient) :-
    ask_symptom(fever),
    ask_symptom(chills),
    ask_symptom(body_ache),
    ask_symptom(fatigue),
    write(Patient), write(' might have an infection.'),
    nl.

diagnose(Patient) :-
    (check_flu(Patient);
     check_diabetes(Patient);
     check_dengue(Patient);
     check_infection(Patient))
    -> true
    ; write('Unable to diagnose the disease based on the symptoms provided.'), nl.

start :-
    write('Enter patient name: '),
    read(Patient),
    diagnose(Patient).


# -----------------------------------------------------------------------------------------------------------------

# symptom_of(fever, flu).
# symptom_of(cough, flu).
# symptom_of(headache, flu).

# symptom_of(runny_nose, cold).
# symptom_of(cough, cold).
# symptom_of(sore_throat, cold).

# symptom_of(chest_pain, pneumonia).
# symptom_of(fever, pneumonia).
# symptom_of(difficulty_breathing, pneumonia).

# ask_symptom(fever) :-
#     write('Do you have a fever? (y/n): '),
#     read(Answer),
#     Answer = y.

# ask_symptom(cough) :-
#     write('Do you have a cough? (y/n): '),
#     read(Answer),
#     Answer = y.

# ask_symptom(headache) :-
#     write('Do you have a headache? (y/n): '),
#     read(Answer),
#     Answer = y.

# ask_symptom(runny_nose) :-
#     write('Do you have a runny nose? (y/n): '),
#     read(Answer),
#     Answer = y.

# ask_symptom(sore_throat) :-
#     write('Do you have a sore throat? (y/n): '),
#     read(Answer),
#     Answer = y.

# ask_symptom(chest_pain) :-
#     write('Do you have chest pain? (y/n): '),
#     read(Answer),
#     Answer = y.

# ask_symptom(difficulty_breathing) :-
#     write('Do you have difficulty breathing? (y/n): '),
#     read(Answer),
#     Answer = y.

# % rules
# diagnose(Condition) :-
#     findall(Symptom, symptom_of(Symptom, Condition), Symptoms),
#     check_symptoms(Symptoms),
#     write('\nYou might have '), write(Condition), write('.\n').

# % Check if patient has all symptoms for a condition
# check_symptoms([]).
# check_symptoms([Symptom|Rest]) :-
#     ask_symptom(Symptom),
#     check_symptoms(Rest).

# start_diagnosis :-
#     write('Please answer the following questions with y or n.\n\n'),
#     (diagnose(flu);
#      diagnose(cold);
#      diagnose(pneumonia);
#      write('\nNo specific condition matched your symptoms.\n')),
#      write('\nPlease consult a medical professional for accurate diagnosis.\n').


# /*
# ?- start_diagnosis.
# */