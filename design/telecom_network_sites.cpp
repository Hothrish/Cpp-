/*Problem:
A telecom operator wants to identify network sites that are operationally impacted because of traffic overload, incidents, service importance, and dependency propagation.
The operator stores network site details, site links, traffic records, incident reports, service profiles, and maintenance windows. Your task is to analyse the records and print sites whose impact level is CRITICAL or WARNING.
The impact scores must be calculated using downstream traffic, direct incidents, upstream incident propagation, SLA-critical services, emergency services, active users, latest maintenance state, and priority flag.
Read input from STDIN and print output to STDOUT. Do not print arbitrary strings anywhere in the program, as these contribute to standard output and test cases will fail.
Tables:
Network Sites: siteId, siteName, siteType (CORE/AGGREGATION/ACCESS/EDGE), capacityMbps, priorityFlag (YES/NO)
Site Links: linkId, parentSiteId, childSiteId
Traffic Records: trafficId, siteId, trafficDay, trafficMbps, customerType (RETAIL/ENTERPRISE/GOVERNMENT/EMERGENCY)
Incident Reports: incidentId, siteId, incidentDay, severity (LOW/MEDIUM/HIGH)
Service Profiles: serviceId, siteId, serviceType (VOICE/DATA/IOT/EMERGENCY), activeUsers, slaLevel (STANDARD/PREMIUM/CRITICAL)
Maintenance Windows: maintenanceId, siteId, maintenanceDay, maintenanceType (INSPECTION/REPAIR/SHUTDOWN)
Validity rules, forest structure for site links, feature calculations (directTrafficMbps, downstreamTrafficMbps, directHighIncident, mediumIncidentCount, upstreamHighIncidentImpact, criticalServiceCount, emergencyServiceExists, activeUserCount, latestMaintenanceType), and the impact score table (with CRITICAL ≥14, WARNING 8-13, NORMAL <8) — all matched what I coded earlier.
Output format: SiteName-ImpactLevel-ImpactScore-DownstreamTrafficMbps, sites separated by #, sorted by CRITICAL before WARNING → higher score → higher downstream traffic → original input order. Print NA if none qualify.*/
#include <bits/stdc++.h>
using namespace std;

struct Site {
    string siteId, siteName, siteType, priorityFlag;
    long long capacityMbps;
    int inputIndex;
};

struct Link {
    string linkId, parentSiteId, childSiteId;
};

struct Traffic {
    string trafficId, siteId, customerType;
    int trafficDay;
    long long trafficMbps;
};

struct Incident {
    string incidentId, siteId, severity;
    int incidentDay;
};

struct Service {
    string serviceId, siteId, serviceType, slaLevel;
    long long activeUsers;
};

struct Maintenance {
    string maintenanceId, siteId, maintenanceType;
    int maintenanceDay;
};

string solve(int referenceDay, vector<Site> &sites, vector<Link> &links, vector<Traffic> &trafficRecords,
             vector<Incident> &incidentReports, vector<Service> &serviceProfiles,
             vector<Maintenance> &maintenanceWindows) {
    string finalOutput = "NA1";

    int n = sites.size();
    unordered_map<string,int> idx;
    idx.reserve(n*2);
    for (int i = 0; i < n; i++) idx[sites[i].siteId] = i;

    static const unordered_set<string> VALID_CUSTOMER = {"RETAIL","ENTERPRISE","GOVERNMENT","EMERGENCY"};
    static const unordered_set<string> VALID_SEVERITY = {"LOW","MEDIUM","HIGH"};
    static const unordered_set<string> VALID_SERVICE_TYPE = {"VOICE","DATA","IOT","EMERGENCY"};
    static const unordered_set<string> VALID_SLA = {"STANDARD","PREMIUM","CRITICAL"};
    static const unordered_set<string> VALID_MAINT = {"INSPECTION","REPAIR","SHUTDOWN"};

    vector<int> parentIdx(n, -1);
    vector<vector<int>> children(n);

    for (auto &lk : links) {
        auto itp = idx.find(lk.parentSiteId);
        auto itc = idx.find(lk.childSiteId);
        if (itp == idx.end() || itc == idx.end()) continue;
        if (lk.parentSiteId == lk.childSiteId) continue;
        int p = itp->second, c = itc->second;
        parentIdx[c] = p;
        children[p].push_back(c);
    }

    vector<long long> directTraffic(n, 0);
    for (auto &t : trafficRecords) {
        auto it = idx.find(t.siteId);
        if (it == idx.end()) continue;
        if (t.trafficDay < 1 || t.trafficDay > referenceDay) continue;
        if (t.trafficMbps < 0) continue;
        if (VALID_CUSTOMER.find(t.customerType) == VALID_CUSTOMER.end()) continue;
        directTraffic[it->second] += t.trafficMbps;
    }

    vector<bool> directHigh(n, false);
    vector<int> mediumCount(n, 0);
    for (auto &inc : incidentReports) {
        auto it = idx.find(inc.siteId);
        if (it == idx.end()) continue;
        if (inc.incidentDay < 1 || inc.incidentDay > referenceDay) continue;
        if (VALID_SEVERITY.find(inc.severity) == VALID_SEVERITY.end()) continue;
        int s = it->second;
        if (inc.severity == "HIGH") directHigh[s] = true;
        else if (inc.severity == "MEDIUM") mediumCount[s]++;
    }

    vector<int> criticalServiceCount(n, 0);
    vector<bool> emergencyExists(n, false);
    vector<long long> activeUserCount(n, 0);
    for (auto &sv : serviceProfiles) {
        auto it = idx.find(sv.siteId);
        if (it == idx.end()) continue;
        if (sv.activeUsers < 0) continue;
        if (VALID_SERVICE_TYPE.find(sv.serviceType) == VALID_SERVICE_TYPE.end()) continue;
        if (VALID_SLA.find(sv.slaLevel) == VALID_SLA.end()) continue;
        int s = it->second;
        activeUserCount[s] += sv.activeUsers;
        if (sv.slaLevel == "CRITICAL") criticalServiceCount[s]++;
        if (sv.serviceType == "EMERGENCY") emergencyExists[s] = true;
    }

    vector<bool> hasMaint(n, false);
    vector<int> latestDay(n, -1);
    vector<string> latestType(n, "NONE");
    for (auto &m : maintenanceWindows) {
        auto it = idx.find(m.siteId);
        if (it == idx.end()) continue;
        if (m.maintenanceDay < 1 || m.maintenanceDay > referenceDay) continue;
        if (VALID_MAINT.find(m.maintenanceType) == VALID_MAINT.end()) continue;
        int s = it->second;
        if (!hasMaint[s] || m.maintenanceDay >= latestDay[s]) {
            hasMaint[s] = true;
            latestDay[s] = m.maintenanceDay;
            latestType[s] = m.maintenanceType;
        }
    }

    vector<int> roots;
    for (int i = 0; i < n; i++) if (parentIdx[i] == -1) roots.push_back(i);

    vector<int> postOrder;
    {
        vector<int> stk(roots.begin(), roots.end());
        while (!stk.empty()) {
            int node = stk.back(); stk.pop_back();
            postOrder.push_back(node);
            for (int c : children[node]) stk.push_back(c);
        }
    }
    reverse(postOrder.begin(), postOrder.end());

    vector<long long> downstream(n, 0);
    for (int node : postOrder) {
        long long total = directTraffic[node];
        for (int c : children[node]) total += downstream[c];
        downstream[node] = total;
    }

    vector<bool> upstreamHigh(n, false);
    {
        vector<int> q(roots.begin(), roots.end());
        size_t qi = 0;
        while (qi < q.size()) {
            int node = q[qi++];
            bool val = upstreamHigh[node] || directHigh[node];
            for (int c : children[node]) {
                upstreamHigh[c] = val;
                q.push_back(c);
            }
        }
    }

    struct ResultEntry {
        string name;
        int levelRank;
        long long score;
        long long downstreamVal;
        int origIndex;
    };
    vector<ResultEntry> results;

    for (int i = 0; i < n; i++) {
        long long score = 0;
        long long cap = sites[i].capacityMbps;
        long long ds = downstream[i];

        if (ds > cap) {
            score += 5;
            if (ds >= 2 * cap) score += 4;
        }
        if (directHigh[i]) score += 5;
        if (mediumCount[i] >= 2) score += 3;
        if (upstreamHigh[i]) score += 4;
        if (criticalServiceCount[i] >= 1) score += 3;
        if (emergencyExists[i]) score += 4;
        if (activeUserCount[i] >= 10000) score += 3;
        if (latestType[i] == "SHUTDOWN") score += 3;
        if (!hasMaint[i]) score += 2;
        if (sites[i].priorityFlag == "YES") score += 2;

        int levelRank = -1;
        if (score >= 14) levelRank = 0;
        else if (score >= 8) levelRank = 1;

        if (levelRank != -1) {
            results.push_back({sites[i].siteName, levelRank, score, ds, sites[i].inputIndex});
        }
    }

    sort(results.begin(), results.end(), [](const ResultEntry &a, const ResultEntry &b) {
        if (a.levelRank != b.levelRank) return a.levelRank < b.levelRank;
        if (a.score != b.score) return a.score > b.score;
        if (a.downstreamVal != b.downstreamVal) return a.downstreamVal > b.downstreamVal;
        return a.origIndex < b.origIndex;
    });

    if (results.empty()) {
        finalOutput = "NA";
    } else {
        string out;
        for (size_t i = 0; i < results.size(); i++) {
            if (i > 0) out += "#";
            string levelStr = (results[i].levelRank == 0) ? "CRITICAL" : "WARNING";
            out += results[i].name + "-" + levelStr + "-" + to_string(results[i].score) + "-" + to_string(results[i].downstreamVal);
        }
        finalOutput = out;
    }

    return finalOutput;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int referenceDay, siteCount, linkCount, trafficCount, incidentCount, serviceCount, maintenanceCount;
    cin >> referenceDay >> siteCount >> linkCount >> trafficCount >> incidentCount >> serviceCount >>
        maintenanceCount;

    vector<Site> sites;
    sites.reserve(siteCount);
    for (int i = 0; i < siteCount; i++) {
        Site x;
        cin >> x.siteId >> x.siteName >> x.siteType >> x.capacityMbps >> x.priorityFlag;
        x.inputIndex = i;
        sites.push_back(x);
    }

    vector<Link> links(linkCount);
    for (auto &x : links) {
        cin >> x.linkId >> x.parentSiteId >> x.childSiteId;
    }

    vector<Traffic> trafficRecords(trafficCount);
    for (auto &x : trafficRecords) {
        cin >> x.trafficId >> x.siteId >> x.trafficDay >> x.trafficMbps >> x.customerType;
    }

    vector<Incident> incidentReports(incidentCount);
    for (auto &x : incidentReports) {
        cin >> x.incidentId >> x.siteId >> x.incidentDay >> x.severity;
    }

    vector<Service> serviceProfiles(serviceCount);
    for (auto &x : serviceProfiles) {
        cin >> x.serviceId >> x.siteId >> x.serviceType >> x.activeUsers >> x.slaLevel;
    }

    vector<Maintenance> maintenanceWindows(maintenanceCount);
    for (auto &x : maintenanceWindows) {
        cin >> x.maintenanceId >> x.siteId >> x.maintenanceDay >> x.maintenanceType;
    }

    cout << solve(referenceDay, sites, links, trafficRecords, incidentReports, serviceProfiles,
                  maintenanceWindows);
    return 0;
}
