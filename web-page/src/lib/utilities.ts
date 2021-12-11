function isEven(number: number): boolean {
	if (number % 2 === 0) return true;

	return false;
}

export function parseCSV(csv: string): SensorData[] {
	const lines = csv.split('\n');

	const dataSets: SensorData[] = [];

	for (let i = 0; i < lines.length; i++) {
		const fields = lines[i].split(',');

		let currentDataSet: SensorData | undefined;

		for (let j = 0; j < fields.length - 1; j++) {
			if (!isEven(j + 1)) {
				currentDataSet = dataSets.find(({ ID }) => ID === Number(fields[j]));

				if (!currentDataSet) {
					currentDataSet = { ID: Number(fields[j]), data: [] };
					dataSets.push(currentDataSet);
				}
			} else {
				currentDataSet?.data.push({
					y: Number(fields[j]),
					x: Number(fields[fields.length - 1]) * 1000
				});
			}
		}
	}

	return dataSets;
}

export function fillTheLastXValue(sensorsData: SensorData[]): SensorData[] {
	let biggerXValue = 0;

	// Find the biggest X value
	for (let i = 0; i < sensorsData.length; i++) {
		const lastDataObject = sensorsData[i].data[sensorsData[i].data.length - 1];
		if (lastDataObject.x > biggerXValue) {
			biggerXValue = lastDataObject.x;
		}
	}

	// Push new values to fill the x end gap
	for (let i = 0; i < sensorsData.length; i++) {
		const lastDataObject = sensorsData[i].data[sensorsData[i].data.length - 1];
		if (biggerXValue > lastDataObject.x) {
			sensorsData[i].data.push({ y: lastDataObject.y, x: biggerXValue });
		}
	}

	return sensorsData;
}

export function filterDatasetsByDate(datasets: Dataset[], from: string, to: string): Dataset[] {
	if (!from || !to) {
		return datasets;
	}

	const splitedFrom = from.split('-');
	const splitedTo = to.split('-');

	const numberSplitedFrom = splitedFrom.map(Number);
	const numberSplitedTo = splitedTo.map(Number);

	const fromDate = Date.UTC(numberSplitedFrom[0], numberSplitedFrom[1], numberSplitedFrom[3]);
	const toDate = Date.UTC(numberSplitedTo[0], numberSplitedTo[1], numberSplitedTo[2]);

	const filteredDatasets: Dataset[] = [];

	for (let i = 0; i < datasets.length; i++) {
		const data = datasets[i].data;
		const filteredData: Dataset['data'] = [];

		for (let j = 0; j < data.length; j++) {
			if (data[j].x >= fromDate && data[j].x <= toDate) {
				filteredData.push(data[j]);
			} else if (data[j].x > toDate) {
				break;
			}
		}
		filteredDatasets.push({
			label: datasets[i].label,
			borderColor: datasets[i].borderColor,
			data: filteredData
		});
	}
	return filteredDatasets;
}
