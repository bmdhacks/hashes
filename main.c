#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <mach/clock.h>
#include <mach/mach.h>

#include <Judy.h>

#include "binarytree.h"
#include "hash.h"

int main(int argc, char *argv[])
{
	FILE *fd;
	char line[256];
	char *tmp;

	// stopwatch
	long duration;
	mach_timespec_t start, finish;

	// 10 randomly selected key values to search for on our benchmark
	const char* keys[] = {
		"aNzMPdlznQEvEoeSHvRfYrTk",
		"capryloneunweldable",
		"azgUuQAbQsUltjsCYQLXesIN",
		"Cynthiaromerillo",
		"podlikegonyalgia",
		"destructivismwindbore",
		"prjjJZseNzaZYhzhFIIuDmya",
		"bjbTouKULCtOYcRFMLKaXWBc",
		"CleYpYRHWEyFufMpHoEUpPce",
		"PeruginesqueTriuris",
		"AunOugkIKYKaihIIsUJaoErH",
		"BfwphNhoGyhkhWPWgalwwdKb",
		"AyLwwvYaGBYWGylUDugCVOXB",
		"ckHmildwEhGUdYdeDEvMQvTb",
		"philomusicalclubbism",
		"oCyQHUPcCSYBAEIheBODnnmN",
		"staphyloraphichomogenic",
		"xclLFGFueRiwPbgbHhDLdSZM",
		"muchnessinductee",
		"jslczKAnaFpDRPtzhxTPsGSz",
		"iOJdVBVyMmucVpYgPQSAioTh",
		"PRiinaYyyjznanFAsJtBmwOR",
		"FQxPbvUxZAFSoYJNYLyVfYDB",
		"FMUMceOHfMukPzLTRWNgKITP",
		"countercriticismunprofuseness",
		"QmchfggYQzItngwzxirbvfBb",
		"unpaunchtrappist",
		"osseocartilaginouslentigo",
		"OwCvxhmGWzowdVKCZyCPXfCr",
		"FnuXxiOpTBTPMaUCeFvxURGW",
		"perturbedequitably",
		"wpklNJKDKvdKceddjwkhzKZD",
		"burgusneoterist",
		"amoralistPisan",
		"rLsQSdvdqKDPgbPrmJioUHzE",
		"unglassedlatinism",
		"Pantagruelinecircumference",
		"unrufflereincarnation",
		"Condyluranonstress",
		"premonetarysatyr",
		"nonserouszapas",
		"OjMqCyztwuDzWhyvMmRIDgbJ",
		"untidilybulldogged",
		"fwMLAyqaSJOnOcLfoJZBWCtf",
		"DXbNNNxKhhSrfvDRFkmrNViw",
		"defeudalizesare",
		"eIBEawGzABUTZwZOXMpLBqTk",
		"manitophenanthridone",
		"qctjesXsUaqWKIemWgSgJdBi",
		"gamophagyepicleidian",
		"QHaIZJxhjJNUOsbZhYZilHmO",
		"WZWGNGVMZPFmXgmnYLbkzzIy",
		"supergrantabatement",
		"Quianganmackintosh",
		"appreciativelyHebraic",
		"homozygouswillful",
		"insomnolentuninsulate",
		"DIGbTPRVxHhtimcVTeNynuLy",
		"euthanasyautoschediaze",
		"JeFPhDKXpIPQIBlelqxYqpjr",
		"protogenalinnoxiously",
		"yUvjyVirlXauljOYiozlwfBg",
		"preadjustableskiogram",
		"Pharaonicalphenol",
		"scouthpublicize",
		"IOnxxuZdiEXnwsMmWhHgClEU",
		"ceMbDnktRvRzxreAgNdnScih",
		"mPpmvcvIolexWHMfzFPnlkJP",
		"intitulesoce",
		"fluoridizecrile",
		"veritablywiesenboden",
		"SyAbSOnetyYLJLdWuBkhdtFB",
		"qPVJXUuiCabTeqeKSqWzHRfL",
		"streltzisinglesticker",
		"MZHdkfgqnUHRDrgklsoAZNgw",
		"FGgByLPvmkVjhHjIrVsUNXHT",
		"dpkOSPxfLQCXGUKzxhSUrFoA",
		"popeyegrinderman",
		"efyUMdtfAvciXUfTjHuuylHk",
		"multiflagellatedacraniate",
		"sumlessnesshyperpencil",
		"eopxIdAyJyFWqcvmxwKvLPmn",
		"QqCKCIPOftDKWltuFTINDptu",
		"AbjoOwHSkHWhetRGXVOtABBk",
		"storybookcomplanation",
		"BUHnFxGuwwENGFiSOWZUMMJM",
		"malleinizewe",
		"CHhvyynIXgVboiFQhsoTATaJ",
		"barbionlirate",
		"pedanticismdishonorableness",
		"rjCcKzGrLxOIONFXqhpvAbtN",
		"RyXkrRRqEvitMuFdrtURbMTI",
		"GPXkGZdbMUdWuyjkykAkjQeZ",
		"IBeTImMAeTZpHqzQRwqDGFAC",
		"dnOOgnDFVfoPJZGDYxjWXAQI",
		"dicerunispiral",
		"RrasAPqtZsziwuqHrkSMzlYk",
		"AkdRBMqLaQGdQjEhoZGcNYlb",
		"bLKRvUZTuEcTtChNlgDuNVfK",
		"truantrytrindle"
	};
	
	/* set up the clock */
	clock_serv_t cclock;
	host_get_clock_service(mach_host_self(), REALTIME_CLOCK, &cclock);

	// binarytree
	binarytree* bt = binarytree_create();

	// JudySL array
	Pvoid_t PJSLArray = (Pvoid_t) NULL;  // initialize JudySL array
	Word_t * PValue;                     // JudySL array entry

	// hashtable
	hashtable *ht = hashtable_create();

	fd = fopen(argv[1], "r");
	if (!fd) {
		printf("could not open dictionary");
		exit(1);
	}

	/* Build our data structures */
	while (fgets(line, sizeof(line), fd)) {
		dict_ent* ent;
		tmp = strchr(line, '\n');
		*tmp = 0;
		ent = dict_create(line, strlen(line));

		// binarytree
		binarytree_insert(&bt, &dict_cmp, ent, sizeof(dict_ent));

		// judy
		JSLI(PValue, PJSLArray, (const uint8_t *)line);
		*PValue = strlen(line);

		// hashtable
		hashtable_insert(ht, line, strlen(line));
	}

	/************************************************************
	 * time each structure */

	// binarytree
	clock_get_time(cclock, &start);
	for (int i=0; i<100; i++) {
		dict_ent ent;
		dict_ent *found;

		strncpy(ent.key, keys[i], MAX_WORDSIZE);
		ent.value = strlen(line);
		found = binarytree_find(bt, &dict_cmp, &ent);
		
		if (found == NULL) {
			printf("Not found\n");
		}
	}
	clock_get_time(cclock, &finish);
	duration = (finish.tv_sec - start.tv_sec) * 1000000;
	duration = duration + finish.tv_nsec - start.tv_nsec;
	printf("%10s total duration: %10ld nanoseconds\n", "binarytree", duration);

	// judy
	clock_get_time(cclock, &start);
	for (int i=0; i<100; i++) {

		JSLG(PValue, PJSLArray, (const uint8_t *)keys[i])
		
		if (PValue == NULL) {
			printf("Not found\n");
		}
	}
	clock_get_time(cclock, &finish);
	duration = (finish.tv_sec - start.tv_sec) * 1000000;
	duration = duration + finish.tv_nsec - start.tv_nsec;
	printf("%10s total duration: %10ld nanoseconds\n", "Judy", duration);

	// hash
	clock_get_time(cclock, &start);
	for (int i=0; i<100; i++) {
		int value = hashtable_get(ht, keys[i]);

		if (value == -1) {
			printf("Not found\n");
		}
	}
	clock_get_time(cclock, &finish);
	duration = (finish.tv_sec - start.tv_sec) * 1000000;
	duration = duration + finish.tv_nsec - start.tv_nsec;
	printf("%10s total duration: %10ld nanoseconds\n", "hash", duration);

	mach_port_deallocate(mach_task_self(), cclock);
}
