% Facts: Symptoms associated with diseases
symptom(fever, flu).
symptom(cough, flu).
symptom(headache, flu).
symptom(runny_nose, flu).
symptom(body_ache, flu).

symptom(fever, covid).
symptom(cough, covid).
symptom(shortness_of_breath, covid).
symptom(loss_of_taste, covid).
symptom(loss_of_smell, covid).

symptom(chest_pain, heart_disease).
symptom(shortness_of_breath, heart_disease).
symptom(fatigue, heart_disease).
symptom(swelling_legs, heart_disease).
symptom(irregular_heartbeat, heart_disease).

symptom(rash, measles).
symptom(fever, measles).
symptom(runny_nose, measles).
symptom(conjunctivitis, measles).

% Rule to diagnose disease based on symptoms
has_disease(Patient, Disease) :-
    symptom(Symptom1, Disease),
    symptom(Symptom2, Disease),
    write(Patient), write(' might have '), write(Disease),
    nl.

% Ask the user about symptoms
ask_symptom(Symptom) :-
    write('Do you have '), write(Symptom), write('? (yes/no): '),
    read(Response),
    Response = yes.

% Rule for flu diagnosis
check_flu(Patient) :-
    ask_symptom(fever),
    ask_symptom(cough),
    ask_symptom(runny_nose),
    ask_symptom(headache),
    write(Patient), write(' might have flu.'),
    nl.

% Rule for covid diagnosis
check_covid(Patient) :-
    ask_symptom(fever),
    ask_symptom(cough),
    ask_symptom(shortness_of_breath),
    ask_symptom(loss_of_taste),
    ask_symptom(loss_of_smell),
    write(Patient), write(' might have COVID-19.'),
    nl.

% Rule for heart disease diagnosis
check_heart_disease(Patient) :-
    ask_symptom(chest_pain),
    ask_symptom(shortness_of_breath),
    ask_symptom(fatigue),
    ask_symptom(swelling_legs),
    ask_symptom(irregular_heartbeat),
    write(Patient), write(' might have heart disease.'),
    nl.

% Rule for measles diagnosis
check_measles(Patient) :-
    ask_symptom(fever),
    ask_symptom(rash),
    ask_symptom(runny_nose),
    ask_symptom(conjunctivitis),
    write(Patient), write(' might have measles.'),
    nl.

% Main diagnosis function
diagnose(Patient) :-
    check_flu(Patient);
    check_covid(Patient);
    check_heart_disease(Patient);
    check_measles(Patient).

% Start diagnosis
start :-
    write('Enter patient name: '),
    read(Patient),
    diagnose(Patient).
