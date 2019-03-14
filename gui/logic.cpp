#include <iostream>
#include <vector>
#include <algorithm>
#include "mainwindow.h"


QVector<QString> required(QString trackReq) {
    QSqlQuery qry;

    if(trackReq == "Computational Science") {
        qry.prepare("SELECT sname, lname FROM not_taken WHERE cs_track_req = 1 OR core = 1");
    }
    else if(trackReq == "Computer Networks") {
        qry.prepare("SELECT sname FROM not_taken WHERE cn_track_req = 1 OR core = 1");
    }
    else if(trackReq == "Computer Security") {
        qry.prepare("SELECT sname FROM not_taken WHERE csec_track_req = 1 OR core = 1");
    }
    else if(trackReq == "Computer Networks") {
        qry.prepare("SELECT sname FROM not_taken WHERE cn_track_req = 1 OR core = 1");
    }
    else if(trackReq == "Database and Informatics") {
        qry.prepare("SELECT sname FROM not_taken WHERE cn_track_req = 1 OR core = 1");
    }
    else {
        qry.prepare("SELECT sname FROM not_taken WHERE sdev_track_req = 1 OR core = 1");
    }

    QVector<QString> req;

    if(qry.exec()) {
        while(qry.next()) {
            QString s = qry.value(0).toString() + " " + qry.value(1).toString();
            req.push_back(s);
        }
    }
    else {
        //ui->COURSE_OUTPUT->addItem("Invalid Read");
        req.push_back("Invalid Read");
    }
    return req;
}

QVector<QString> nextTerm(QString term) { //, vector<string> taken, string track
  QSqlQuery query;
  QVector<QString> couldTake;
  if (term == "Fall") {
    query.prepare("SELECT subject, number,prereq1,prereq2 FROM not_taken WHERE fall = 1");
  }
  else if (term == "Winter") {
    query.prepare("SELECT subject, number,prereq1,prereq2 FROM not_taken WHERE winter = 1");
  }
  else if (term == "Spring") {
    query.prepare("SELECT subject, number,prereq1,prereq2 FROM not_taken WHERE spring = 1");
  }
  if (query.exec()) {
    while (query.next()) {
      QSqlQuery check;
      QString p1 = query.value(2).toString();
      QString p2 = query.value(3).toString();
      check.prepare("select * from not_taken where not exists(select 1 from not_taken where sname = (:p1) or sname = (:p2))");
      check.bindValue(":p1",p1);
      check.bindValue(":p2",p2);
      if(check.exec()) {
          QString prev = "";
          while(check.next()) {
              if (query.value(1).toString() != prev)
               {
                QString s = query.value(0).toString() + " " + query.value(1).toString();
                couldTake.push_back(s);
                prev = query.value(1).toString();
              }
          }
        }
    }
  }
  else {
    //ui->COURSE_OUTPUT->addItem("Invalid Read");
      couldTake.push_back("Invalid Read");
  }
  return couldTake;
}

//QVector<QVector<QString>> path(QString term)
QVector<QVector<QString> > path(QString track, QString nextTerm) {

    // path<term<classes>
    QVector<QVector<QString>> p(9);
    for(int term = 0; term < 9; term++) {  //9 terms, could change later
        //QVector<QString> t;
        //p.push_back(t);
        p[term].resize(4);
    }

    for(auto term = p.begin(); term!=p.end(); term++) {
        (*term).push_back("Hey");
    }


    return p;

}
