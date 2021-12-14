<script lang="ts">
	import Chart from '$lib/components/Chart.svelte';
	import Irrigation from '$lib/components/Irrigation.svelte';
	import TimePicker from '$lib/components/TimePicker.svelte';
	import { parseCSV, filterDatasetsByDate, alignXAxisBegginingEnd } from '$lib/utilities';
	import State from '$lib/state';
	import { onMount } from 'svelte';

	const sensorsDecoration = [
		{ label: 'Umidade do Ar %', color: '#009dff' },
		{ label: 'Temperatura ºC', color: '#fc4b6f' },
		{ label: 'Umidade do Solo %', color: '#e5682b' }
	];

	let datasets: Dataset[] = [];
	let filteredDatasets: Dataset[] = [];
	let filteredAlignedDatasets: Dataset[] = [];
	let minDate: number;
	let maxDate: number;

	$: filteredDatasets = filterDatasetsByDate(datasets, $State.get('from'), $State.get('to'));
	$: filteredAlignedDatasets = alignXAxisBegginingEnd(filteredDatasets);

	onMount(async () => {
		try {
			const csv = await fetch('/sensorData.csv');
			const parsedSensorData = parseCSV(await csv.text());

			const updatedDatasets: Dataset[] = [];

			for (let i = 0; i < parsedSensorData.length; i++) {
				const sensorData = sensorsDecoration[parsedSensorData[i].ID - 1];

				updatedDatasets.push({
					label: sensorData.label,
					data: parsedSensorData[i].data,
					borderColor: sensorData.color
				});
			}

			datasets = updatedDatasets;
			minDate = datasets[0].data[0].x;
			maxDate = datasets[0].data[datasets[0].data.length - 1].x;
		} catch (err) {
			console.error(err);
			alert("Can't access sensor data file!");
		}
	});
</script>

<div>
	<Chart title="Horta Inteligente" datasets={filteredAlignedDatasets} min={-5} max={100} />
</div>
<TimePicker {minDate} {maxDate} />
<Irrigation />

<style>
	div {
		aspect-ratio: 2/1;
		max-width: 100%;
		max-height: 100%;
		margin-bottom: 24px;
	}
</style>
